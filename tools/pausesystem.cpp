#include "pausesystem.h"
#include "loading.h"

PauseSystem::PauseSystem()
{
	free();
}

PauseSystem::~PauseSystem()
{
	free();
}

void PauseSystem::free()
{
	active = false;
	key_released = false;
}



void PauseSystem::load(const float &screen_w, const float &screen_h)
{
	free();

	Loading::add(text.setFont(cmm::JCANDLE_FONT_PATH));
	if (Loading::isError())	return;
	text.setText("GAME PAUSED");
	text.setSize(screen_h / 10);
	text.setFillColor(cmm::WHITISH_COLOR);
	text.center(screen_w / 2, screen_h / 2);

	Loading::add(click.load("sounds/click.wav"));
	if (Loading::isError())	return;

	Loading::add(blackout.create(static_cast<int>(screen_w), static_cast<int>(screen_h)));
	if (Loading::isError())	return;
	blackout.setColor(cmm::BACKGROUND_COLOR);
}

void PauseSystem::handle(const sf::Event &event)
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

void PauseSystem::draw(sf::RenderWindow* &window)
{
	window->draw(blackout);
	window->draw(text);
}

void PauseSystem::fadein(const float &v, const int &max)
{
	blackout.fadein(v, max);
	text.fadein(v, max);
}

void PauseSystem::fadeout(const float &v, const int &min)
{
	blackout.fadeout(v, min);
	text.fadeout(v, min);
}



const bool& PauseSystem::isActive() const
{
	return active;
}

void PauseSystem::turnOnOff()
{
	active = !active;
}

float PauseSystem::getAlpha() const
{
	return blackout.getAlpha();
}

void PauseSystem::setVolume(const float &volume)
{
	click.setVolume(volume);
}
