#include "knightspecs.h"
#include "logconsole.h"
#include "user.h"
#include "loading.h"
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
			it = nullptr;
		}

		values.clear();
	}

	if (!features.empty())
	{
		features.clear();
	}
}



void Knightspecs::load(const float &screen_w, const float &screen_h)
{
	free();

	this->screen_w = screen_w;
	this->screen_h = screen_h;

	Loading::add(plank.load("images/other/plank.png"));
	if (Loading::isError())	return;
	plank.setScale(screen_w / 2560, screen_h / 1440);
	plank.setPosition(-screen_h / 256, screen_h / 5.5);
	plank.setColor(sf::Color(0xE0, 0xE0, 0xE0));

	Loading::add(topgear.load("images/other/gear.png"));
	Loading::add(botgear.load("images/other/gear.png"));
	if (Loading::isError())	return;
	topgear.setOrigin(topgear.getWidth() * 0.5, topgear.getHeight() * 0.5);
	botgear.setOrigin(botgear.getWidth() * 0.5, botgear.getHeight() * 0.5);
	topgear.setScale(screen_w / 2560, screen_h / 1440);
	botgear.setScale(screen_w / 2560, screen_h / 1440);
	topgear.setPosition(0, plank.getTop());
	botgear.setPosition(0, plank.getBot());

	max_offset = 10;
	Loading::add(knight.load("images/other/menuknight.png", max_offset));
	if (Loading::isError())	return;
	knight.setScale(screen_w / 2560, screen_h / 1440);
	knight.setPosition(screen_w / 7.6, screen_h - screen_h / 72 - knight.getHeight());

	// click.load("sounds/click.wav");

	Loading::add(categories.setFont("fonts/jcandlestickextracond.ttf"));
	if (Loading::isError())	return;
	categories.setText("Heart Points:\nMagic Points:\nArmour:\nMagic Resistant:\nMovement Speed:\nDamage:\nMagic Damage:\nLuck:\nExperience:\nLevel:");
	categories.setFillColor(cmm::LogConsole::getLockedColor());
	categories.setSize(screen_h / 28);
	categories.setPosition(screen_h / 128, plank.getTop() + screen_h / 72);

	features.clear();
	for (unsigned i = 0; i < FEATURES::SIZE; ++i)
	{
		values.push_back(new cmm::Text);
		Loading::add(values[i]->setFont("fonts/jcandlestickextracond.ttf"));
		if (Loading::isError())	return;
		values[i]->setText("loading...");
		values[i]->setFillColor(cmm::LogConsole::getLoadingColor());
		values[i]->setSize(screen_h / 28);
		features.push_back(0);
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

void Knightspecs::mechanics(const double &elapsedTime)
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

void Knightspecs::fadein(const float &v, const int &max)
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

void Knightspecs::fadeout(const float &v, const int &min)
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
				it->setFillColor(cmm::LogConsole::getLoadingColor());
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
	request.setMessage("username=" + cmm::User::getUsername());
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
			features.clear();
			std::string result = request.getResult(), buf = "";
			std::vector<std::string> strs;
			for (unsigned i = 0; i < result.size(); ++i)
			{
				if (result[i] == '@')
				{
					features.push_back(boost::lexical_cast<int>(buf));
					strs.push_back(buf);
					buf = "";
					continue;
				}

				buf += result[i];
			}

			values[HEART_POINTS]->setText(strs[HEART_POINTS] + " hp");
			values[MAGIC_POINTS]->setText(strs[MAGIC_POINTS] + " mp");
			values[ARMOUR]->setText(floatToStr(boost::lexical_cast<float>(strs[ARMOUR]) / 100) + " %");
			values[MAGIC_RESISTANT]->setText(floatToStr(boost::lexical_cast<float>(strs[MAGIC_RESISTANT]) / 100) + " %");
			values[MOVEMENT_SPEED]->setText(strs[MOVEMENT_SPEED] + " %");
			values[DAMAGE]->setText(strs[DAMAGE] + " dmg");
			values[MAGIC_DAMAGE]->setText(strs[MAGIC_DAMAGE] + " mdmg");
			values[LUCK]->setText(strs[LUCK] + " %");
			values[EXPERIENCE]->setText(strs[EXPERIENCE] + " %");
			values[LEVEL]->setText(strs[LEVEL] + " lv");
			strs.clear();

			values[HEART_POINTS]->setFillColor(cmm::LogConsole::getRedColor());
			values[MAGIC_POINTS]->setFillColor(cmm::LogConsole::getBlueColor());
			values[ARMOUR]->setFillColor(cmm::LogConsole::getLockedColor());
			values[MAGIC_RESISTANT]->setFillColor(cmm::LogConsole::getLockedColor());
			values[MOVEMENT_SPEED]->setFillColor(cmm::LogConsole::getGreenColor());
			values[DAMAGE]->setFillColor(cmm::LogConsole::getRedColor());
			values[MAGIC_DAMAGE]->setFillColor(cmm::LogConsole::getBlueColor());
			values[LUCK]->setFillColor(cmm::LogConsole::getSuccessColor());
			values[EXPERIENCE]->setFillColor(cmm::LogConsole::getSuccessColor());
			values[LEVEL]->setFillColor(cmm::LogConsole::getSuccessColor());

			thread.success = true;
		}
	}

	// Error.
	if (!success)
	{
		for (auto &it : values)
		{
			it->setText("error");
			it->setFillColor(cmm::LogConsole::getErrorColor());
		}
	}

	position();
	thread.ready = true;
}

const bool& Knightspecs::isReady() const
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

std::string Knightspecs::floatToStr(float value)
{
	std::string buf = std::to_string(value);
	for (size_t i = buf.size() - 1; i >= 0; --i)
	{
		if (buf[i] == '0')
			buf.erase(i);
		else
			break;
	}

	return buf;
}

//void Knightspecs::setVolume(const float &volume)
//{
//	click.setVolume(volume);
//}