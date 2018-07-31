#include "state.h"

State::State()
{
	free();
}

State::~State()
{
	free();
}

void State::free()
{
	prev = next = exit = false;
}

bool State::isPrev() const
{
	return prev && isReady();
}

bool State::isNext() const
{
	return next && isReady();
}

bool State::isExit() const
{
	return exit && isReady();
}

bool State::isState() const
{
	return prev || next || exit;
}



char* User::username = (char*)"user";



sf::Clock FPS::clock = sf::Clock();
float FPS::currentTime = 0;
unsigned FPS::fps = 0;

double FPS::counter = 0;
double FPS::max = 0.25;	// every 0.25sec have the ability to getFPS()

void FPS::mechanics(double elapsedTime)
{
	fps = 1.f / currentTime;
	currentTime = clock.restart().asSeconds();
	counter += elapsedTime;
}

bool FPS::timePassed()
{
	if (counter > max)
	{
		counter = 0;
		return true;
	}

	return false;
}

const unsigned& FPS::getFPS()
{
	return fps;
}