// Test of objects: 
#include "core.h"
#include "levelmenu.h"

Core* core = new Core(0, sf::Color(21, 21, 29, 0xFF));
LevelMenu* levelMenu = new LevelMenu;

enum STATES
{
	MENU = 3,
	LEVELMENU,
	PLATFORM
};

int main(int argc, char** argv)
{
	core->create("Combat Halloween");
	core->state = LEVELMENU;
	levelMenu->load(core->getWidth(), core->getHeight());

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
			case LEVELMENU: levelMenu->handle(core->getEvent()); 	break;
			}
		}

		if (core->state == LEVELMENU)
		{
			levelMenu->mechanics(core->getElapsedTime());
			levelMenu->draw(core->getWindow());

			if (levelMenu->isPrev())
			{
				levelMenu->reset();
				--core->state;
			}
			else if (levelMenu->isNext())
			{
				levelMenu->reset();
				++core->state;
			}
			else if (levelMenu->isExit())
			{
				levelMenu->reset();
				core->open = false;
			}
		}

		core->display();
	}

	delete core;
	delete levelMenu;
	return 0;
}