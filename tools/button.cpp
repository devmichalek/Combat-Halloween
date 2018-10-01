#include "button.h"
#include "loading.h"

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

	Loading::add(click.load("sounds/click.wav"));
	Loading::add(button.load(path, numOfOffsets));
	if (Loading::isError())	return;

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

void Button::setVolume(const float &volume)
{
	click.setVolume(volume);
}

void Button::draw(sf::RenderWindow* &window)
{
	window->draw(button);
}

void Button::fadein(const float &v, const int &max)
{
	button.fadein(v, max);
}

void Button::fadeout(const float &v, const int &min)
{
	button.fadeout(v, min);
}

const float& Button::getLeft() const
{
	return button.getLeft();
}

float Button::getRight() const
{
	return button.getRight();
}

const float& Button::getTop() const
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
