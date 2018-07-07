#include "button.h"

Button::Button()
{
	locked = false;
}

Button::~Button()
{
	locked = false;
}

void Button::load(const char* path, bool locked, int numOfOffsets)
{
	free();

	click.load("sounds/click.wav");
	button.load(path, numOfOffsets);

	this->locked = locked;
	locked ? button.setOffset(numOfOffsets - 1) : button.setOffset(0);
}

void Button::setPosition(float x, float y)
{
	button.setPosition(x, y);
}

void Button::setScale(float x, float y)
{
	button.setScale(x, y);
}

void Button::setVolume(float volume)
{
	click.setVolume(volume);
}

void Button::draw(sf::RenderWindow* &window)
{
	window->draw(button.get());
}

void Button::fadein(float v, int max)
{
	button.fadein(v, max);
}

void Button::fadeout(float v, int min)
{
	button.fadeout(v, min);
}

float Button::getLeft() const
{
	return button.getLeft();
}

float Button::getRight() const
{
	return button.getRight();
}

float Button::getTop() const
{
	return button.getTop();
}

float Button::getBot() const
{
	return button.getBot();
}

float Button::getWidth() const
{
	return button.getWidth();
}

float Button::getHeight() const
{
	return button.getHeight();
}

void Button::lock()
{
	if (!locked)
	{
		locked = true;
		button.setOffset(2);
	}
}

void Button::unlock()
{
	if (locked)
	{
		locked = false;
		button.setOffset(0);
	}
}

void Button::reset()
{
	free();
	locked ? button.setOffset(button.getNumOfOffsets() - 1) : button.setOffset(0);
}




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

void SquareButton::handle(sf::Event& event)
{
	if (!locked)
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (button.checkCollision(event.mouseButton.x, event.mouseButton.y))
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

bool Circlebutton::handle(sf::Event& event)
{
	if (!locked)
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (button.checkCollisionCircle(event.mouseButton.x, event.mouseButton.y))
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

bool Circlebutton::isActive()
{
	return active;
}

void Circlebutton::setActive(bool active)
{
	this->active = active;
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
	url = "";
}

void LinkButton::handle(sf::Event& event)
{
	if (!locked)
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (button.checkCollisionCircle(event.mouseButton.x, event.mouseButton.y))
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




VolumeButton::VolumeButton() :min(0), max(100)
{
	free();
}

VolumeButton::~VolumeButton()
{
	free();
}

void VolumeButton::free()
{
	volume = 0;
	locked = false;
	plus_pressed = false;
	minus_pressed = false;
}



void VolumeButton::load(float screen_w, float screen_h)
{
	free();

	click.load("sounds/click.wav");

	plus.load("images/buttons/plus.png", 3);
	plus.setScale(screen_w / 2560, screen_h / 1440);

	minus.load("images/buttons/minus.png", 3);
	minus.setScale(screen_w / 2560, screen_h / 1440);
}

void VolumeButton::setPosition(float left, float right, float bot)
{
	plus.setPosition(right - plus.getWidth(), bot - plus.getHeight() / 1.2);
	minus.setPosition(left, bot - minus.getHeight() / 1.2);
}

bool VolumeButton::handle(sf::Event& event)
{
	if (!locked)
	{
		if (event.type == sf::Event::MouseButtonReleased)
		{

			plus.setOffset(0);
			minus.setOffset(0);
			plus_pressed = false;
			minus_pressed = false;

		}
	}

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			float x = event.mouseButton.x;
			float y = event.mouseButton.y;

			if (plus.checkCollisionCircle(x, y))
			{
				if (!locked)
				{
					if (volume < max)
					{
						click.play();
					}

					plus_pressed = true;
				}

				return true;
			}
			else if (minus.checkCollisionCircle(x, y))
			{
				if (!locked)
				{
					if (volume > min)
					{
						click.play();
					}

					minus_pressed = true;
				}

				return true;
			}
		}
	}

	return false;
}

void VolumeButton::draw(sf::RenderWindow* &window)
{
	window->draw(plus.get());
	window->draw(minus.get());
}

void VolumeButton::mechanics(double elapsedTime)
{
	if (plus_pressed && volume < max)
	{
		volume += elapsedTime * 0xFF / 4;
		if (volume > max)
		{
			volume = max;
		}

		plus.setOffset(1);
	}
	else if (minus_pressed && volume > min)
	{
		volume -= elapsedTime * 0xFF / 4;
		if (volume < min)
		{
			volume = min;
		}

		minus.setOffset(1);
	}
}



void VolumeButton::fadein(float v, int max)
{
	plus.fadein(v, max);
	minus.fadein(v, max);
}

void VolumeButton::fadeout(float v, int min)
{
	plus.fadeout(v, min);
	minus.fadeout(v, min);
}



void VolumeButton::setGlobalVolume(float volume)
{
	this->volume = volume;
}

const float& VolumeButton::getGlobalVolume() const
{
	return volume;
}

void VolumeButton::setLocked(bool locked)
{
	this->locked = locked;

	if (!locked)
	{
		plus.setOffset(0);
		minus.setOffset(0);
	}
	else
	{
		plus.setOffset(2);
		minus.setOffset(2);
	}
}

bool VolumeButton::hasChanged() const
{
	return plus_pressed || minus_pressed;
}

void VolumeButton::setVolume(float volume)
{
	click.setVolume(volume);
}