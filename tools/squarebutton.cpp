#include "squarebutton.h"

SquareButton::SquareButton()
{
	free();
}

SquareButton::~SquareButton()
{
	free();
}

void SquareButton::free()
{
	locked = false;
	pressed = false;
}

void SquareButton::handle(const sf::Event &event)
{
	if (!locked)
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (button.checkCollision((float)event.mouseButton.x, (float)event.mouseButton.y))
				{
					click.play();
					button.setOffset(1);
					pressed = true;
				}
			}
		}
	}
}

void SquareButton::setPressed()
{
	pressed = true;
}

const bool& SquareButton::isPressed() const
{
	return pressed;
}