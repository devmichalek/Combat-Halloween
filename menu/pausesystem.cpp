#include "pausesystem.h"

Pausesystem::Pausesystem()
{
	free();
}

Pausesystem::~Pausesystem()
{
	free();
}

void Pausesystem::free()
{
	active = false;
	key_released = false;
}



void Pausesystem::load(float screen_w, float screen_h)
{
	free();

	text.setFont("fonts/jcandlestickextracond.ttf");
	text.setText("GAME PAUSED");
	text.setSize(screen_h / 10);
	text.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
	text.center(screen_w / 2, screen_h / 2);

	click.load("sounds/click.wav");

	blackout.create(screen_w, screen_h);
	blackout.setColor(sf::Color(0, 0, 0));
}

void Pausesystem::handle(sf::Event& event)
{
	// keyboard stuff
	if (event.type == sf::Event::KeyPressed && !key_released)
	{
		if (event.key.code == 15)	// 'p'
		{
			key_released = true;
			active = !active;
			click.play();
		}
	}

	if (event.type == sf::Event::KeyReleased)
	{
		key_released = false;
	}
}

void Pausesystem::draw(sf::RenderWindow* &window)
{
	window->draw(blackout.get());
	window->draw(text.get());
}

void Pausesystem::fadein(float v, int max)
{
	blackout.fadein(v, max);
	text.fadein(v, max);
}

void Pausesystem::fadeout(float v, int min)
{
	blackout.fadeout(v, min);
	text.fadeout(v, min);
}



const bool& Pausesystem::isActive() const
{
	return active;
}

void Pausesystem::turnOnOff()
{
	active = !active;
}

int Pausesystem::getAlpha() const
{
	return blackout.getAlpha();
}

void Pausesystem::setVolume(float volume)
{
	click.setVolume(volume);
}
