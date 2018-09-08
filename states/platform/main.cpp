// Test of objects: 
#include "core.h"
#include "platform.h"

Core* core = new Core(0, sf::Color(21, 21, 29, 0xFF));
Platform* platform = new Platform;

enum STATES
{
	MENU = 3,
	LEVEL,
	PLATFORM,
	ENDSCENE
};

int main(int argc, char** argv)
{
	core->create("Combat Halloween");
	core->state = PLATFORM;
	platform->load(core->getWidth(), core->getHeight());

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
			case PLATFORM: platform->handle(core->getEvent()); 	break;
			}
		}

		if (core->state == PLATFORM)
		{
			platform->mechanics(core->getElapsedTime());
			platform->draw(core->getWindow());

			if (platform->isPrev() && platform->isNext())
			{
				platform->reset();
				core->state = MENU;
			}
			else if (platform->isPrev())
			{
				platform->reset();
				--core->state;
			}
			else if (platform->isNext())
			{
				platform->reset();
				++core->state;
			}
			else if (platform->isExit())
			{
				platform->reset();
				core->open = false;
			}
		}

		core->display();
	}

	delete core;
	delete platform;
	return 0;
}