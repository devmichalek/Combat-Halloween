#include "state.h"

State::State( int state, bool mSwitch, bool cSwitch, sf::Uint8 mVolume, sf::Uint8 cVolume )
{
	this->state = state;
	this->mSwitch = mSwitch;
	this->cSwitch = cSwitch;
	this->mVolume = mVolume;
	this->cVolume = cVolume;
}

State::~State()
{
	//free
}

void State::operator =( State* state )
{
	this->state = state->state;
	this->mSwitch = state->mSwitch;
	this->cSwitch = state->cSwitch;
	this->mVolume = state->mVolume;
	this->cVolume = state->cVolume;
}

/*
int State::get_state()
{
	return state;
}

bool State::get_mSwitch()
{
	return mSwitch;
}

bool State::get_cSwitch()
{
	return cSwitch;
}

sf::Uint8 State::get_mVolume()
{
	return mVolume;
}

sf::Uint8 State::get_cVolume()
{
	return cVolume;
}
*/