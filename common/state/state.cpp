#include "state.h"

cmm::State::State()
{
	prev = next = exit = false;
}

cmm::State::~State()
{
	prev = next = exit = false;
}



bool cmm::State::isPrev() const
{
	return prev && isReady();
}

bool cmm::State::isNext() const
{
	return next && isReady();
}

bool cmm::State::isExit() const
{
	return exit && isReady();
}

bool cmm::State::isState() const
{
	return prev || next || exit;
}