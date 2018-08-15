#include "core.h"
#include "menu.h"

Core* core = new Core(0, sf::Color(21, 21, 29, 0xFF));
Menu* menu = new Menu;

enum STATES
{
	LOGIN = 2,
	MENU,
	LEVEL,
};

int main(int argc, char** argv)
{
	core->create("Combat Halloween");
	core->state = MENU;
	menu->load(static_cast<float>(core->getWidth()), static_cast<float>(core->getHeight()));

	while (core->open)
	{
		// clear
		core->clear();

		// events, mouse, keyboard
		while (core->isEvent())
		{
			if (core->getEvent().type == sf::Event::Closed)
			{
				core->open = false;
			}

			switch (core->state)
			{
			case MENU: menu->handle(core->getEvent()); 	break;
			}
		}

		if (core->state == MENU)
		{
			menu->mechanics(core->getElapsedTime());
			menu->draw(core->getWindow());

			if (menu->isPrev())
			{
				menu->reset();
				-- core->state;
			}
			else if (menu->isNext())
			{
				menu->reset();
				++ core->state;
			}
			else if (menu->isExit())
			{
				menu->reset();
				core->open = false;
			}
		}

		core->display();
	}

	delete core;
	delete menu;
	return 0;
}