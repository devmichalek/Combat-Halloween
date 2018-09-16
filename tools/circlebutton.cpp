#include "circlebutton.h"

CircleButton::CircleButton()
{
	free();
}

CircleButton::~CircleButton()
{
	free();
}

void CircleButton::free()
{
	locked = false;
	active = false;
	changed = false;
}

bool CircleButton::handle(const sf::Event &event)
{
	if (!locked)
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (button.checkCollisionCircle((float)event.mouseButton.x, (float)event.mouseButton.y))
				{
					click.play();
					changeActive();
					changed = true;
					return true;
				}
			}
		}
	}

	return false;
}

const bool& CircleButton::isActive() const
{
	return active;
}

void CircleButton::setActive(bool active)
{
	this->active = active;
	if(!locked && button.getNumOfOffsets() > 0)
		active ? button.setOffset(1) : button.setOffset(0);
}

void CircleButton::changeActive()
{
	active = !active;
	active ? button.setOffset(1) : button.setOffset(0);
}

bool CircleButton::hasChanged()
{
	if (changed)
	{
		changed = false;
		return true;
	}

	return false;
}

void CircleButton::setChanged(bool changed)
{
	this->changed = changed;
}