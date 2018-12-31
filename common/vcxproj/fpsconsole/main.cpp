#include "core.h"
#include "fpsconsole.h"
#include "converter.h"

int main(int argc, char** argv)
{
	cmm::Core core(0, sf::Color::White);
	core.create("Combat Halloween");

	cmm::FPSConsole fps;

	while (core.open)
	{
		core.clear();

		while (core.isEvent())
			if (core.getEvent().type == sf::Event::Closed)
				core.open = false;



		fps.mechanics(core.getElapsedTime());

		if (fps.timePassed())
		{
			printf("FPS: %f%s", fps.getFPS(), cmm::CSNEWLINE);
		}

		core.getWindow()->display();
	}

	return 0;
}