#include "core.h"
#include "foefactory.h"

Core* core = new Core(0, sf::Color(21, 21, 29, 0xFF));
FoeFactory* foeFactory = new FoeFactory;

enum STATES
{
	LEVELMENU = 4,
	PLATFORM,
	ENDSCENE
};

int main(int argc, char** argv)
{
	core->create("Combat Halloween");
	core->state = PLATFORM;
	foeFactory->load(core->getWidth(), core->getHeight());

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
			default: break;
			}
		}

		if (core->state == PLATFORM)
		{
			foeFactory->mechanics(core->getElapsedTime());
			foeFactory->draw(core->getWindow());
		}

		core->display();
	}

	delete core;
	delete foeFactory;
	return 0;
}