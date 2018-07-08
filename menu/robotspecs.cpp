#include "robotspecs.h"
#include "state.h"
#include "boost/lexical_cast.hpp"

Robotspecs::Robotspecs()
{
	free();
}

Robotspecs::~Robotspecs()
{
	free();
}

void Robotspecs::free()
{
	screen_w = 0;
	screen_h = 0;

	offset = 0;
	max_offset = 0;

	thread.free();

	if (!values.empty())
	{
		for (auto &it : values)
		{
			delete it;
			it = NULL;
		}

		values.clear();
	}
}



void Robotspecs::load(float screen_w, float screen_h)
{
	free();

	this->screen_w = screen_w;
	this->screen_h = screen_h;

	plank.load("images/other/plank.png");
	plank.setScale(screen_w / 2560, screen_h / 1440);
	plank.setPosition(-screen_h / 256, screen_h / 5.5);
	plank.setColor(sf::Color(0xE0, 0xE0, 0xE0));

	topgear.load("images/other/gear.png");
	botgear.load("images/other/gear.png");
	topgear.setOrigin(topgear.getWidth() * 0.5, topgear.getHeight() * 0.5);
	botgear.setOrigin(botgear.getWidth() * 0.5, botgear.getHeight() * 0.5);
	topgear.setScale(screen_w / 2560, screen_h / 1440);
	botgear.setScale(screen_w / 2560, screen_h / 1440);
	topgear.setPosition(0, plank.getTop());
	botgear.setPosition(0, plank.getBot());

	max_offset = 10;
	robot.load("images/other/menurobot.png", max_offset);
	robot.setScale(screen_w / 2560, screen_h / 1440);
	robot.setPosition(screen_w / 6.5, screen_h - screen_h / 72 - robot.getHeight());

	click.load("sounds/click.wav");

	categories.setFont("fonts/jcandlestickextracond.ttf");
	categories.setText("Heart Points:\nArmour:\nSpeed:\nClip:\nShoot Damage:\nLaser Beam Damage:\nLuckiness:\nExperience:");
	categories.setFillColor(Username::getLockedColor());
	categories.setSize(screen_h / 28);
	categories.setPosition(screen_h / 128, plank.getTop() + screen_h / 24);

	for (unsigned i = 0; i < AMOUNT; ++i)
	{
		values.push_back(new cmm::Text);
		values[i]->setFont("fonts/jcandlestickextracond.ttf");
		values[i]->setText("loading...");
		values[i]->setFillColor(Username::getLoadingColor());
		values[i]->setSize(screen_h / 28);
	}

	position();
}

void Robotspecs::draw(sf::RenderWindow* &window)
{
	window->draw(plank.get());
	window->draw(topgear.get());
	window->draw(botgear.get());
	window->draw(robot.get());
	window->draw(categories.get());
	
	for (auto &it : values)
	{
		window->draw(it->get());
	}
}

void Robotspecs::mechanics(double elapsedTime)
{
	// Delete thread if is ready
	if (thread.ready)
	{
		thread.reset();
	}

	// Offset.
	offset += elapsedTime * 25;
	if (offset > max_offset)	offset = 0;
	robot.setOffset(offset);
}

void Robotspecs::fadein(float v, int max)
{
	plank.fadein(v, max);
	topgear.fadein(v, max);
	botgear.fadein(v, max);
	robot.fadein(v, max);
	categories.fadein(v, max);

	for (auto &it : values)
	{
		it->fadein(v, max);
	}
}

void Robotspecs::fadeout(float v, int min)
{
	plank.fadeout(v, min);
	topgear.fadeout(v, min);
	botgear.fadeout(v, min);
	robot.fadeout(v, min);
	categories.fadeout(v, min);

	for (auto &it : values)
	{
		it->fadeout(v, min);
	}
}



void Robotspecs::setThread()
{
	if (!thread.success)
	{
		if (!thread.ready && !thread.thread)
		{
			// Values.
			for (auto &it : values)
			{
				it->setText("loading...");
				it->setFillColor(Username::getLoadingColor());
			}

			position();

			thread.thread = new std::thread(&Robotspecs::setValues, this);
			thread.thread->detach();
		}
	}
}

void Robotspecs::reloadThread()
{
	thread.success = false;
}

void Robotspecs::setValues()
{
	cmm::Request request;
	request.setMessage("username=" + boost::lexical_cast<std::string>(Username::getUsername()));
	request.setRequest("/combathalloween/getparts.php", sf::Http::Request::Post);
	request.setHttp("http://adrianmichalek.pl/");

	bool success = request.sendRequest();
	if (success)
	{
		if (request.getResult() == "0")	// error
		{
			success = false;
		}
		else
		{
			for (auto &it : values)
			{
				it->setText("value");
				it->setFillColor(Username::getSuccessColor());
			}

			thread.success = true;
		}
	}

	// Error.
	if (!success)
	{
		for (auto &it : values)
		{
			it->setText("error");
			it->setFillColor(Username::getErrorColor());
		}
	}

	position();
	thread.ready = true;
}

bool Robotspecs::isReady() const
{
	return thread.success;
}

void Robotspecs::position()
{
	float x = categories.getRight() + screen_h / 27;
	float y = categories.getTop();
	for (unsigned i = 0; i < values.size(); ++i)
	{
		values[i]->setPosition(x, y + screen_h / 27 * i);
	}
}

void Robotspecs::setVolume(float volume)
{
	click.setVolume(volume);
}