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





FPS::FPS()
{
	clock = sf::Clock();
	currentTime = 0;
	fps = 0.0f;

	counter = 0;
	max = 0.25;	// every 0.25sec have the ability to getFPS()
}

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

const float& FPS::getFPS()
{
	return fps;
}