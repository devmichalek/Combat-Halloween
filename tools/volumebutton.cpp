#include "volumebutton.h"
#include "loading.h"

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
	changed = false;
	plus_pressed = false;
	minus_pressed = false;
}



void VolumeButton::load(const float &screen_w, const float &screen_h)
{
	free();

	Loading::add(click.load("sounds/click.wav"));

	Loading::add(plus.load("images/buttons/plus.png", 3));
	if (Loading::isError())	return;
	plus.setScale(screen_w / 2560, screen_h / 1440);

	Loading::add(minus.load("images/buttons/minus.png", 3));
	if (Loading::isError())	return;
	minus.setScale(screen_w / 2560, screen_h / 1440);
}

void VolumeButton::setPosition(float left, float right, float bot)
{
	plus.setPosition(right - plus.getWidth(), bot - plus.getHeight() / 1.2);
	minus.setPosition(left, bot - minus.getHeight() / 1.2);
}

bool VolumeButton::handle(const sf::Event &event)
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
			float x = (float)event.mouseButton.x;
			float y = (float)event.mouseButton.y;

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
	window->draw(plus);
	window->draw(minus);
}

void VolumeButton::mechanics(double elapsedTime)
{
	if (plus_pressed && volume < max)
	{
		volume += static_cast<float>(elapsedTime) * 0xFF / 4;
		if (volume > max)
		{
			volume = max;
		}

		plus.setOffset(1);
	}
	else if (minus_pressed && volume > min)
	{
		volume -= static_cast<float>(elapsedTime) * 0xFF / 4;
		if (volume < min)
		{
			volume = min;
		}

		minus.setOffset(1);
	}
}



void VolumeButton::fadein(const float &v, const int &max)
{
	plus.fadein(v, max);
	minus.fadein(v, max);
}

void VolumeButton::fadeout(const float &v, const int &min)
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

const bool VolumeButton::hasChanged()
{
	bool status = plus_pressed || minus_pressed || changed;
	changed = false;
	return status;
}

void VolumeButton::setChanged(float newVolume)
{
	volume = newVolume;
	changed = true;
}

void VolumeButton::setVolume(const float &volume)
{
	click.setVolume(volume);
}