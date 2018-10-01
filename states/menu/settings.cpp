#include "settings.h"
#include "logconsole.h"
#include "loading.h"


Settings::Settings()
{
	free();
}

Settings::~Settings()
{
	free();
}

void Settings::free()
{
	screen_w = 0;
	screen_h = 0;

	if (!keys.empty())
	{
		keys.clear();
	}

	if (!text_collisions.empty())
	{
		text_collisions.clear();
	}

	if (!state_texts.empty())
	{
		for (auto &it : state_texts)
		{
			delete it;
			it = nullptr;
		}

		state_texts.clear();
	}
	
	if (!active_texts.empty())
	{
		for (auto &it : active_texts)
		{
			delete it;
			it = nullptr;
		}

		active_texts.clear();
	}

	if (!gears.empty())
	{
		for (auto &it : gears)
		{
			delete it;
			it = nullptr;
		}

		gears.clear();
	}

	tableMoves = 0;
	x1 = x2 = 0;

	chartMoves = 0;
	y1 = y2 = 0;

	target = -1;
}



void Settings::load(const float &screen_w, const float &screen_h)
{
	free();

	this->screen_w = screen_w;
	this->screen_h = screen_h;

	// Set font for state texts and active texts.
	const char* text_path = cmm::JCANDLE_FONT_PATH;
	for (unsigned i = 0; i < AMOUNT; ++i)
	{
		state_texts.push_back(new cmm::Text);
		Loading::add(state_texts[i]->setFont(text_path));
		if (Loading::isError())	return;
		active_texts.push_back(new cmm::Text);
		active_texts[i]->setFont(text_path);
	}

	// Set text for state texts.
	state_texts[MOVE_LEFT]->setText("move left");
	state_texts[MOVE_RIGHT]->setText("move right");
	state_texts[JUMP]->setText("jump");
	state_texts[ATTACK]->setText("attack");
	state_texts[SHIELD]->setText("shield");
	state_texts[JUMP_ATTACK]->setText("jump attack");
	state_texts[JUMP_SHIELD]->setText("jump shield");
	state_texts[PAUSE]->setText("pause");
	state_texts[CHAT]->setText("chat");

	// Set active_texts text.
	keys.clear();
	for (unsigned i = 0; i < AMOUNT; ++i)
	{
		text_collisions.push_back(sf::Rect<float>());
		keys.push_back(-1);
		active_texts[i]->setText("loading...");
	}
	active_texts[PAUSE]->setText("p");
	active_texts[CHAT]->setText("o");

	// Set size of state texts and active texts.
	int size = static_cast<int>(screen_h / 28);
	for (unsigned i = 0; i < AMOUNT; ++i)
	{
		state_texts[i]->setSize(size);
		active_texts[i]->setSize(size);
		state_texts[i]->setFillColor(cmm::LogConsole::getLockedColor());
		i < JUMP_ATTACK ? active_texts[i]->setFillColor(cmm::LogConsole::getLoadingColor()) : active_texts[i]->setFillColor(cmm::LogConsole::getLockedColor());
	}

	// Set contact me information.
	Loading::add(contactme.setFont(text_path));
	if (Loading::isError())	return;
	contactme.setText("Contact me: devmichalek@gmail.com");
	contactme.setSize(size);
	contactme.setFillColor(cmm::LogConsole::getLoadingColor());

	// Set table.
	Loading::add(table.load("images/other/plank.png"));
	if (Loading::isError())	return;
	table.setScale(screen_w / 2560, screen_h / 1440);
	x1 = screen_w - screen_w / 128;
	x2 = screen_w + screen_w / 64 - table.getWidth();
	table.setPosition(x1, screen_h / 2.6);

	// Set second table.
	Loading::add(chart.load("images/other/splank.png"));
	if (Loading::isError())	return;
	chart.setScale(screen_w / 2560, screen_h / 1440);
	y1 = screen_h - screen_h / 72;
	y2 = screen_h + screen_h / 72 - chart.getHeight();
	chart.setPosition(screen_w / 2.13, y1);

	// Set gears.
	for (unsigned i = 0; i < RIGHT + 1; ++i)
	{
		gears.push_back(new cmm::Sprite);
		Loading::add(gears[i]->load("images/other/gear.png"));
		if (Loading::isError())	return;
		gears[i]->setOrigin(gears[i]->getWidth() * 0.5, gears[i]->getHeight() * 0.5);
		gears[i]->setScale(screen_w / 2560, screen_h / 1440);
	}
	gears[TOP]->setPosition(screen_w, table.getTop());
	gears[BOT]->setPosition(screen_w, table.getBot());
	gears[LEFT]->setPosition(chart.getLeft(), screen_h);
	gears[RIGHT]->setPosition(chart.getRight(), screen_h);

	// Set reset button.
	Loading::add(resetbutton.load("images/buttons/resetbutton.png", 3));
	if (Loading::isError())	return;
	resetbutton.setScale(screen_w / 2560, screen_h / 1440);

	// Set info.
	Loading::add(info.setFont(cmm::JCANDLE_FONT_PATH));
	if (Loading::isError())	return;
	info.setText("Press new key to change.\nClick anywhere to save.");
	info.setSize(size);
	info.setFillColor(sf::Color(0xDD, 0xDD, 0xDD));

	// Position.
	positionTable();
	positionChart();

	// Load sounds.
	Loading::add(click.load("sounds/click.wav"));
	if (Loading::isError())	return;

	setCoxing();
}

bool Settings::handle(const sf::Event &event)
{
	if (chartMoves == 0 && target != -1)
	{
		// Reset.
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (resetbutton.checkCollision(float(event.mouseButton.x), float(event.mouseButton.y), 0.0f, 0.0f))
				{
					resetbutton.setOffset(1);
					resetCoxing();
					return true;
				}
			}
		}

		if (event.type == sf::Event::MouseButtonReleased)
		{
			resetbutton.setOffset(0);
		}

		// Keyboard stuff.
		if (event.type == sf::Event::KeyPressed)
		{
			bool success = true;
			for (auto &it : keys)
			{
				if (it == event.key.code)
				{
					success = false;
					break;
				}
			}

			// Set key.
			if (success)
			{
				if (isPossibleKey(event.key.code))
				{
					click.play();

					keys[target] = event.key.code;
					saveKeys();

					active_texts[target]->setText(getName(event.key.code));
					active_texts[target]->setFillColor(cmm::LogConsole::getErrorColor());

					if (target == ATTACK || target == JUMP)
					{
						active_texts[JUMP_ATTACK]->setText(getName(keys[JUMP]) + " + " + getName(keys[ATTACK]));
					}
					else if (target == SHIELD || target == JUMP)
					{
						active_texts[JUMP_SHIELD]->setText(getName(keys[JUMP]) + " + " + getName(keys[SHIELD]));
					}

					positionTable();
				}
			}
		}
	}

	if (tableMoves == 0 && table.getX() == x2)	// Table is fully visible.
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				// Set default color if target is set.
				if (target != -1)
				{
					active_texts[target]->setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
				}

				// Check if it is collide.
				target = -1;
				for (unsigned i = 0; i < JUMP_ATTACK; ++i)
				{
					if (text_collisions[i].contains(float(event.mouseButton.x), float(event.mouseButton.y)))
					{
						target = i;
						click.play();
						active_texts[i]->setFillColor(sf::Color(0xF2, 0x58, 0x3E));
						break;
					}
				}

				if (target != -1)
				{
					return true;
				}
			}
		}
	}

	return false;
}

void Settings::draw(sf::RenderWindow* &window)
{
	window->draw(table);
	window->draw(chart);

	for (auto &it : state_texts)
	{
		window->draw(*it);
	}

	for (auto &it : active_texts)
	{
		window->draw(*it);
	}

	window->draw(contactme);
	window->draw(info);
	window->draw(resetbutton);

	for (auto &it : gears)
	{
		window->draw(*it);
	}
}

void Settings::mechanics(const double &elapsedTime)
{
	if (tableMoves != 0)	// is moving
	{
		table.move(tableMoves, 0);

		positionTable();

		float rotation = static_cast<float>(elapsedTime) * 0xFF;
		if (tableMoves < 0)
		{
			gears[TOP]->setRotation(gears[TOP]->getRotation() + rotation);
			gears[BOT]->setRotation(gears[BOT]->getRotation() - rotation);
		}
		else
		{
			gears[TOP]->setRotation(gears[TOP]->getRotation() - rotation);
			gears[BOT]->setRotation(gears[BOT]->getRotation() + rotation);
		}
	}

	if (target != -1)
	{
		chart.getY() > y2 ? chartMoves = -(float)elapsedTime * 0xFF : chartMoves = 0.0f;

		if (chart.getY() < y2)
		{
			chart.setPosition(chart.getX(), y2);
		}
	}
	else
	{
		chart.getY() < y1 ? chartMoves = (float)elapsedTime * 0xFF : chartMoves = 0.0f;

		if (chart.getY() > y1)
		{
			chart.setPosition(chart.getX(), y1);
		}
	}

	if (chartMoves != 0) // is moving
	{
		positionChart();
		chart.move(0, chartMoves);

		float rotation = static_cast<float>(elapsedTime) * 0xFF;
		if (chartMoves < 0)
		{
			gears[LEFT]->setRotation(gears[LEFT]->getRotation() - rotation);
			gears[RIGHT]->setRotation(gears[RIGHT]->getRotation() + rotation);
		}
		else
		{
			gears[LEFT]->setRotation(gears[LEFT]->getRotation() + rotation);
			gears[RIGHT]->setRotation(gears[RIGHT]->getRotation() - rotation);
		}
	}
}



void Settings::fadein(const float &v, const int &max)
{
	for (auto &it : state_texts)
	{
		it->fadein(v, max);
	}

	for (auto &it : active_texts)
	{
		it->fadein(v, max);
	}

	for (auto &it : gears)
	{
		it->fadein(v, max);
	}

	contactme.fadein(v, max);
	table.fadein(v, max);
	chart.fadein(v, max);
	info.fadein(v, max);
	resetbutton.fadein(v, max);
}

void Settings::fadeout(const float &v, const int &min)
{
	for (auto &it : state_texts)
	{
		it->fadeout(v, min);
	}

	for (auto &it : active_texts)
	{
		it->fadeout(v, min);
	}

	for (auto &it : gears)
	{
		it->fadeout(v, min);
	}

	contactme.fadeout(v, min);
	table.fadeout(v, min);
	chart.fadeout(v, min);
	info.fadeout(v, min);
	resetbutton.fadeout(v, min);
}



void Settings::exsertTable(const double &elapsedTime)
{
	table.getX() > x2 ? tableMoves = -(float)elapsedTime * 0xFF : tableMoves = 0.0f;

	if (table.getX() < x2)
	{
		table.setPosition(x2, table.getY());
		positionTable();
	}
}

void Settings::shovelTable(const double &elapsedTime)
{
	table.getX() < x1 ? tableMoves = (float)elapsedTime * 0xFF : tableMoves = 0.0f;
	
	if (table.getX() > x1)
	{
		table.setPosition(x1, table.getY());
		positionTable();
	}
}

void Settings::resetCoxing()
{
	resetKeys();
	reloadCoxing();
}

void Settings::setCoxing()
{
	loadKeys();
	reloadCoxing();
}

void Settings::reloadCoxing()
{
	for (unsigned i = 0; i < JUMP_ATTACK; ++i)
	{
		active_texts[i]->setText(getName(keys[i]));
		active_texts[i]->setFillColor(cmm::LogConsole::getLoadingColor());
	}
	active_texts[JUMP_ATTACK]->setText(getName(keys[JUMP]) + " + " + getName(keys[ATTACK]));
	active_texts[JUMP_SHIELD]->setText(getName(keys[JUMP]) + " + " + getName(keys[SHIELD]));
	active_texts[JUMP_ATTACK]->setFillColor(cmm::LogConsole::getLockedColor());
	active_texts[JUMP_SHIELD]->setFillColor(cmm::LogConsole::getLockedColor());

	positionTable();
}

void Settings::positionTable()
{
	// Position state texts.
	for (unsigned i = 0; i < state_texts.size(); ++i)
	{
		state_texts[i]->setPosition(table.getX() + screen_w / 80, table.getY() + screen_h / 56 + (screen_h / 28 * i) + screen_h / 256);
	}

	// Position active texts.
	for (unsigned i = 0; i < active_texts.size(); ++i)
	{
		active_texts[i]->setPosition(table.getX() + table.getWidth() / 2, state_texts[i]->getY());
		if (i < JUMP_ATTACK)
		{
			text_collisions[i].width = table.getWidth();
			text_collisions[i].height = active_texts[i]->getHeight() *1.5f;
			text_collisions[i].left = table.getX();
			text_collisions[i].top = active_texts[i]->getY();
		}
	}

	// Contactme.
	contactme.setPosition(table.getX() + screen_w / 80, table.getBot() - contactme.getHeight() - screen_h / 54);
}

void Settings::positionChart()
{
	info.setPosition(chart.getX() + screen_w / 80, chart.getY() + screen_h / 54);
	resetbutton.setPosition(chart.getRight() - resetbutton.getWidth(), chart.getBot() - resetbutton.getHeight());
}

const std::string Settings::getName(const int &n)
{
	std::string name = "";

	if (n > -1 && n <= 25)			// from a to z
	{
		// in ASCII 97 is letter 'a'
		name = static_cast <char> (n + 97);
	}
	else if (n >= 26 && n <= 35)	// numbers
	{
		// 26 + 22 = 48
		// in ASCII 48 is character 0
		name = static_cast <char> (n + 22);
	}
	else if (n >= 75 && n <= 84)	// numbers cd.
	{
		// 75 - 27 = 48
		// in ASCII 48 is character 0
		name = static_cast <char> (n - 27);
	}
	else
	{
		switch (n)
		{
		case 71: name = "Left";		break;
		case 72: name = "Right";	break;
		case 73: name = "Up";		break;
		case 74: name = "Down";		break;
		case 57: name = "Space";	break;
		case 37: name = "Left Control";		break;
		case 38: name = "Left Shift";		break;
		case 39: name = "Left Alt";			break;
		case 41: name = "Right Control";	break;
		case 42: name = "Right Shift";		break;
		case 43: name = "Right Alt";		break;
		}
	}

	return name;
}

void Settings::reset()
{
	tableMoves = chartMoves = 0;
	table.setPosition(x1, table.getY());
	chart.setPosition(chart.getX(), y1);
	positionTable();
	positionChart();
}

void Settings::setVolume(const float &volume)
{
	click.setVolume(volume);
}