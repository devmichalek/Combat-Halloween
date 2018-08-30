#include "circlebutton.h"

Circlebutton::Circlebutton()
{
	free();
}

Circlebutton::~Circlebutton()
{
	free();
}

void Circlebutton::free()
{
	locked = false;
	active = false;
	changed = false;
}

bool Circlebutton::handle(const sf::Event &event)
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

const bool& Circlebutton::isActive() const
{
	return active;
}

void Circlebutton::setActive(bool active)
{
	this->active = active;
	if(!locked)
		active ? button.setOffset(1) : button.setOffset(0);
}

void Circlebutton::changeActive()
{
	active = !active;
	active ? button.setOffset(1) : button.setOffset(0);
}

bool Circlebutton::hasChanged()
{
	if (changed)
	{
		changed = false;
		return true;
	}

	return false;
}

void Circlebutton::setChanged(bool changed)
{
	this->changed = changed;
}