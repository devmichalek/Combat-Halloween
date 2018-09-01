#include "core.h"
#include "knight.h"

Core* core = new Core(0, sf::Color(21, 21, 29, 0xFF));
Knight* knight = new Knight;


int main(int argc, char** argv)
{
	core->create("Combat Halloween");
	
	knight->load(core->getWidth(), core->getHeight());
	knight->set(core->getWidth() / 2, core->getHeight() / 2);
	knight->switchCollision();

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

			// knight->handle(core->getEvent());
		}

		knight->mechanics(core->getElapsedTime());
		knight->draw(core->getWindow());

		core->display();
	}

	delete core;
	delete knight;
	return 0;
}