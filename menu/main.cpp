// Test of objects: 
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
	menu->load(core->getWidth(), core->getHeight());

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
			menu->head(core->getWindow(), core->getElapsedTime());

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