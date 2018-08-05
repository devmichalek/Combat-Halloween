#include "knightspecs.h"
#include "state.h"
#include "boost/lexical_cast.hpp"

Knightspecs::Knightspecs()
{
	free();
}

Knightspecs::~Knightspecs()
{
	free();
}

void Knightspecs::free()
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



void Knightspecs::load(float screen_w, float screen_h)
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
	knight.load("images/other/menuknight.png", max_offset);
	knight.setScale(screen_w / 2560, screen_h / 1440);
	knight.setPosition(screen_w / 7.6, screen_h - screen_h / 72 - knight.getHeight());

	click.load("sounds/click.wav");

	categories.setFont("fonts/jcandlestickextracond.ttf");
	categories.setText("Heart Points:\nArmour:\nMovement Speed:\nDamage:\nAttack Speed:\nLuckiness:\nExperience:\nLevel:");
	categories.setFillColor(User::getLockedColor());
	categories.setSize(screen_h / 28);
	categories.setPosition(screen_h / 128, plank.getTop() + screen_h / 24);

	for (unsigned i = 0; i < AMOUNT; ++i)
	{
		values.push_back(new cmm::Text);
		values[i]->setFont("fonts/jcandlestickextracond.ttf");
		values[i]->setText("loading...");
		values[i]->setFillColor(User::getLoadingColor());
		values[i]->setSize(screen_h / 28);
	}

	position();
}

void Knightspecs::draw(sf::RenderWindow* &window)
{
	window->draw(plank.get());
	window->draw(topgear.get());
	window->draw(botgear.get());
	window->draw(knight.get());
	window->draw(categories.get());
	
	for (auto &it : values)
	{
		window->draw(it->get());
	}
}

void Knightspecs::mechanics(double elapsedTime)
{
	// Delete thread if is ready
	if (thread.ready)
	{
		thread.reset();
	}

	// Offset.
	offset += elapsedTime * 25;
	if (offset > max_offset)	offset = 0;
	knight.setOffset(offset);
}

void Knightspecs::fadein(float v, int max)
{
	plank.fadein(v, max);
	topgear.fadein(v, max);
	botgear.fadein(v, max);
	knight.fadein(v, max);
	categories.fadein(v, max);

	for (auto &it : values)
	{
		it->fadein(v, max);
	}
}

void Knightspecs::fadeout(float v, int min)
{
	plank.fadeout(v, min);
	topgear.fadeout(v, min);
	botgear.fadeout(v, min);
	knight.fadeout(v, min);
	categories.fadeout(v, min);

	for (auto &it : values)
	{
		it->fadeout(v, min);
	}
}



void Knightspecs::setThread()
{
	if (!thread.success)
	{
		if (!thread.ready && !thread.thread)
		{
			// Values.
			for (auto &it : values)
			{
				it->setText("loading...");
				it->setFillColor(User::getLoadingColor());
			}

			position();

			thread.thread = new std::thread(&Knightspecs::setValues, this);
			thread.thread->detach();
		}
	}
}

void Knightspecs::reloadThread()
{
	thread.success = false;
}

void Knightspecs::setValues()
{
	cmm::Request request;
	request.setMessage("username=" + boost::lexical_cast<std::string>(User::getUsername()));
	request.setRequest("/combathalloween/getters/getfeatures.php", sf::Http::Request::Post);
	request.setHttp("http://amichalek.pl/");

	bool success = request.sendRequest();
	if (success)
	{
		if (request.getResult() == "0")	// error
		{
			success = false;
		}
		else
		{
			std::string result = request.getResult(), buf = "";
			std::vector<std::string> strs;
			for (unsigned i = 0; i < result.size(); ++i)
			{
				if (result[i] == '@')
				{
					strs.push_back(buf);
					buf = "";
					continue;
				}

				buf += result[i];
			}

			values[HEART_POINTS]->setText(strs[HEART_POINTS] + " hp");
			values[ARMOUR]->setText(strs[ARMOUR] + " %");
			values[MOVEMENT_SPEED]->setText(strs[MOVEMENT_SPEED] + " %");
			values[DAMAGE]->setText(strs[DAMAGE] + " dmg");
			values[ATTACK_SPEED]->setText(strs[ATTACK_SPEED] + " %");
			values[LUCKINESS]->setText(strs[LUCKINESS] + " %");
			values[EXPERIENCE]->setText(strs[EXPERIENCE] + " %");
			values[LEVEL]->setText(strs[LEVEL] + " lv");
			strs.clear();

			values[HEART_POINTS]->setFillColor(User::getErrorColor());
			values[ARMOUR]->setFillColor(User::getLockedColor());
			values[MOVEMENT_SPEED]->setFillColor(User::getGreenColor());
			values[DAMAGE]->setFillColor(User::getErrorColor());
			values[ATTACK_SPEED]->setFillColor(User::getGreenColor());
			values[LUCKINESS]->setFillColor(User::getSuccessColor());
			values[EXPERIENCE]->setFillColor(User::getSuccessColor());
			values[LEVEL]->setFillColor(User::getSuccessColor());

			thread.success = true;
		}
	}

	// Error.
	if (!success)
	{
		for (auto &it : values)
		{
			it->setText("error");
			it->setFillColor(User::getErrorColor());
		}
	}

	position();
	thread.ready = true;
}

bool Knightspecs::isReady() const
{
	return thread.success;
}

void Knightspecs::position()
{
	float x = categories.getRight() + screen_h / 27;
	float y = categories.getTop();
	for (unsigned i = 0; i < values.size(); ++i)
	{
		values[i]->setPosition(x, y + screen_h / 27 * i);
	}
}

void Knightspecs::setVolume(float volume)
{
	click.setVolume(volume);
}