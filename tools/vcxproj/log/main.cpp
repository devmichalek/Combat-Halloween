#include "core.h"
#include "log.h"

int main(int argc, char** argv)
{
	cmm::Core core(0, sf::Color::White);
	core.create("Combat Halloween");

	Log log;
	log.load(core.getWidth(), core.getHeight());

	while (core.open)
	{
		core.clear();

		while (core.isEvent())
		{
			if (core.getEvent().type == sf::Event::Closed)
				core.open = false;

			if (core.getEvent().type == sf::Event::MouseButtonPressed)
			{
				log.addError("sth");
			}
		}

		// core.display();
	}

	return 0;
}