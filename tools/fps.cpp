#include "fps.h"
#include "loading.h"

FPS::FPS()
{
	free();
}

FPS::~FPS()
{
	free();
}

void FPS::free()
{
	position = NONE;
	active = false;
	screen_w = screen_h = 0;
}

void FPS::reset()
{
	active = false;
	text.setText("-");
	text.setAlpha(0xFF);
}



void FPS::load(const float &screen_w, const float &screen_h)
{
	free();

	this->screen_w = screen_w;
	this->screen_h = screen_h;

	Loading::add(text.setFont(cmm::JAPOKKI_FONT_PATH));
	if (Loading::isError())	return;
	text.setSize(screen_w / 60);
	text.setOutlineThickness(1);
	text.setOutlineColor(cmm::BACKGROUND_COLOR);
	text.setFillColor(cmm::LOADING_COLOR);
	text.setAlpha(0xFF);
	text.setText("-");
}

void FPS::draw(sf::RenderWindow* &window)
{
	if (!active)
		return;

	window->draw(text);
}

void FPS::mechanics(const double &elapsedTime)
{
	if (!active)
		return;

	fps.mechanics(elapsedTime);

	if (fps.timePassed())
	{
		std::string result = std::to_string(static_cast<int>(fps.getFPS()));
		text.setText(result);
		setText();
	}
}

void FPS::fadeout(const float &v, const int &min)
{
	text.fadeout(v, min);
}



const bool& FPS::isActive() const
{
	return active;
}

void FPS::setActive(bool active)
{
	this->active = active;
}

void FPS::setLeftTop()
{
	position = LEFT_TOP;
}

void FPS::setRightTop()
{
	position = RIGHT_TOP;
}

void FPS::setLeftBot()
{
	position = LEFT_BOT;
}

void FPS::setRightBot()
{
	position = RIGHT_BOT;
}

void FPS::setText()
{
	switch (position)
	{
	case NONE:
		text.center(screen_w / 2, screen_h / 2);
		break;

	case LEFT_TOP:
		text.setPosition(screen_w / 256, screen_h / 144);
		break;

	case RIGHT_TOP:
		text.setPosition((screen_w  - screen_w / 256) - text.getWidth(), screen_h / 144);
		break;

	case LEFT_BOT:
		text.setPosition(screen_w / 256, (screen_h - screen_h / 72) - text.getHeight());
		break;

	case RIGHT_BOT:
		text.setPosition((screen_w - screen_w / 256) - text.getWidth(), (screen_h - screen_h / 72) - text.getHeight());
		break;
	}
}