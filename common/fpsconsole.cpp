#include "fpsconsole.h"

cmm::FPSConsole::FPSConsole()
{
	clock = sf::Clock();
	currentTime = 0;
	fps = 0.0f;

	counter = 0;
	max = 0.25;	// every 0.25sec have the ability to getFPS()
}

cmm::FPSConsole::~FPSConsole()
{
	currentTime = 0;
	fps = 0.0f;
	counter = 0;
}



void cmm::FPSConsole::mechanics(const double &elapsedTime)
{
	fps = 1.f / currentTime;
	currentTime = clock.restart().asSeconds();
	counter += elapsedTime;
}

bool cmm::FPSConsole::timePassed()
{
	if (counter > max)
	{
		counter = 0;
		return true;
	}

	return false;
}

const float& cmm::FPSConsole::getFPS()
{
	return fps;
}