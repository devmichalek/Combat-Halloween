#include "linkbutton.h"
#include "converter.h"

LinkButton::LinkButton()
{
	free();
}

LinkButton::~LinkButton()
{
	free();
}

void LinkButton::free()
{
	locked = false;
	url = cmm::SEMPTY;
}

void LinkButton::handle(const sf::Event &event)
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
					openWebsite();
					button.setOffset(1);
				}
			}
		}

		if (event.type == sf::Event::MouseButtonReleased)
		{
			button.setOffset(0);
		}
	}
}

void LinkButton::setUrl(std::string newUrl)
{
	url = newUrl;
}

void LinkButton::openWebsite()
{
	std::string command = "start " + url;
	system(command.c_str());
}