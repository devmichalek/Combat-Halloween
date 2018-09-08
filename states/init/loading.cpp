#include "loading.h"

Loading::Loading()
{
	free();
}

Loading::~Loading()
{
	free();
}

void Loading::free()
{
	screen_w = 0;
	screen_h = 0;
	ready = false;
	state = 0;
}

void Loading::load(const float &screen_w, const float &screen_h)
{
	free();

	this->screen_w = screen_w;
	this->screen_h = screen_h;

	// Set text.
	text.setFont("fonts/Jaapokki-Regular.otf");
	setText();
	text.setSize(screen_h / 24);
	text.setAlpha(0xFF);

	// Set progress bar.
	progress_bar.load("images/other/progress_bar.png", 7);
	progress_bar.setScale(screen_w / 1707, screen_h / 960);
	progress_bar.setAlpha(0xFF);
	progress_bar.setPosition(screen_w / 2 - progress_bar.getWidth() / 2, screen_h / 2 + screen_h / 36);
}

void Loading::draw(sf::RenderWindow* &window)
{
	window->draw(text.get());
	window->draw(progress_bar.get());
}

void Loading::mechanics(const double &elapsedTime)
{
	if (ready)
	{
		int min = 0;
		text.fadeout((float)elapsedTime * 0xFF * 2, min);
		progress_bar.fadeout((float)elapsedTime * 0xFF * 2, min);
	}
	else
	{
		setText();
		state++;
		progress_bar.setOffset(state%7);
	}
}



const sf::Uint8& Loading::getState() const
{
	return state;
}

bool Loading::isReady() const
{
	return ready && progress_bar.getAlpha() == 0;
}



void Loading::beReady()
{
	ready = true;
}

void Loading::setText()
{
	text.setText("Loading " + std::to_string(state) + "%");
	text.setPosition(screen_w / 2 - text.getWidth() / 2 + screen_w / 160, screen_h / 2 - text.getHeight() / 2 - screen_h / 72);
}