#include "buttonstate.h"

int ButtonState::counter = 0;
int ButtonState::currentID = 0;
bool ButtonState::action = false;
bool ButtonState::newAction = false;

const int& ButtonState::getCurrentID()
{
	return currentID;
}

const bool& ButtonState::isAction()
{
	return action;
}

const bool& ButtonState::isNewAction()
{
	return newAction;
}

Button::Button()
{
	++counter;
	ID = counter;
	button = nullptr;
}

Button::~Button()
{
	free();
}

void Button::free()
{
	if (button)
		delete button;
}

const int& Button::getID() const
{
	return ID;
}