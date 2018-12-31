#include "knightspecs.h"
#include "user.h"
#include "loading.h"
#include "converter.h"

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
	plank.setColor(cmm::DULL_IRON_COLOR);

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
	categories.setText(	"Heart Points:" 	+ cmm::SNEWLINE + 
						"Magic Points:" 	+ cmm::SNEWLINE + 
						"Armour:" 			+ cmm::SNEWLINE + 
						"Magic Resistant:" 	+ cmm::SNEWLINE + 
						"Movement Speed:" 	+ cmm::SNEWLINE + 
						"Damage:" 			+ cmm::SNEWLINE + 
						"Magic Damage:" 	+ cmm::SNEWLINE + 
						"Luck:" 			+ cmm::SNEWLINE + 
						"Experience:" 		+ cmm::SNEWLINE + 
						"Level:");
	categories.setFillColor(cmm::LOCKED_COLOR);
	categories.setSize(screen_h / 28);
	categories.setPosition(screen_h / 128, plank.getTop() + screen_h / 72);

	features.clear();
	for (unsigned i = 0; i < FEATURES::SIZE; ++i)
	{
		values.push_back(new cmm::Text);
		Loading::add(values[i]->setFont("fonts/jcandlestickextracond.ttf"));
		if (Loading::isError())	return;
		values[i]->setText("loading...");
		values[i]->setFillColor(cmm::LOADING_COLOR);
		values[i]->setSize(screen_h / 28);
		features.push_back(0);
	}

	position();
}

void Knightspecs::draw(sf::RenderWindow* &window)
{
	window->draw(plank);
	window->draw(topgear);
	window->draw(botgear);
	window->draw(knight);
	window->draw(categories);
	
	for (auto &it : values)
	{
		window->draw(*it);
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
				it->setFillColor(cmm::LOADING_COLOR);
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
	request.setRequest(cmm::WEBSITE_SUBPATH + "getters/getfeatures.php", sf::Http::Request::Post);
	request.setHttp(cmm::WEBSITE_PATH);

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
			std::string result = request.getResult(), buf = cmm::SEMPTY;
			std::vector<std::string> strs;
			for (unsigned i = 0; i < result.size(); ++i)
			{
				if (result[i] == '@')
				{
					features.push_back(boost::lexical_cast<int>(buf));
					strs.push_back(buf);
					buf = cmm::SEMPTY;
					continue;
				}

				buf += result[i];
			}

			values[HEART_POINTS]->setText(strs[HEART_POINTS] + " hp");
			values[MAGIC_POINTS]->setText(strs[MAGIC_POINTS] + " mp");
			values[ARMOUR]->setText(cmm::floatToStr(boost::lexical_cast<float>(strs[ARMOUR]) / 100) + " %");
			values[MAGIC_RESISTANT]->setText(cmm::floatToStr(boost::lexical_cast<float>(strs[MAGIC_RESISTANT]) / 100) + " %");
			values[MOVEMENT_SPEED]->setText(strs[MOVEMENT_SPEED] + " %");
			values[DAMAGE]->setText(strs[DAMAGE] + " dmg");
			values[MAGIC_DAMAGE]->setText(strs[MAGIC_DAMAGE] + " mdmg");
			values[LUCK]->setText(strs[LUCK] + " %");
			values[EXPERIENCE]->setText(strs[EXPERIENCE] + " %");
			values[LEVEL]->setText(strs[LEVEL] + " lv");
			strs.clear();

			values[HEART_POINTS]->setFillColor(cmm::RED_COLOR);
			values[MAGIC_POINTS]->setFillColor(cmm::BLUE_COLOR);
			values[ARMOUR]->setFillColor(cmm::LOCKED_COLOR);
			values[MAGIC_RESISTANT]->setFillColor(cmm::LOCKED_COLOR);
			values[MOVEMENT_SPEED]->setFillColor(cmm::GREEN_COLOR);
			values[DAMAGE]->setFillColor(cmm::RED_COLOR);
			values[MAGIC_DAMAGE]->setFillColor(cmm::BLUE_COLOR);
			values[LUCK]->setFillColor(cmm::SUCCESS_COLOR);
			values[EXPERIENCE]->setFillColor(cmm::SUCCESS_COLOR);
			values[LEVEL]->setFillColor(cmm::SUCCESS_COLOR);

			thread.success = true;
		}
	}

	// Error.
	if (!success)
	{
		for (auto &it : values)
		{
			it->setText("error");
			it->setFillColor(cmm::ERROR_COLOR);
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