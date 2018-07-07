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



char* Username::username = (char*)"error";

char* Username::getUsername()
{
	return username;
}