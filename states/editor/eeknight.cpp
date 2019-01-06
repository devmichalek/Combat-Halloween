#include "eeknight.h"
#include "loading.h"
#include "converter.h"

ee::KnightBoard::KnightBoard()
{
	free();
}

ee::KnightBoard::~KnightBoard()
{
	free();
}

void ee::KnightBoard::free()
{
	sclaimer = false;

	if (!mins.empty())		mins.clear();
	if (!maxs.empty())		maxs.clear();
	if (!values.empty())	values.clear();
	if (!ratios.empty())	ratios.clear();
	if (!states.empty())	states.clear();
	if (!rects.empty())		rects.clear();
	if (!texts.empty())
	{
		for (auto &it : texts)
		{
			delete it;
			it = nullptr;
		}

		texts.clear();
	}
}

void ee::KnightBoard::load(sf::Vector2f &screen)
{
	Loading::add(board.load("images/other/splank.png"));
	if (Loading::isError())	return;

	board.setScale(screen.x / 3200, screen.y / 720);

	for (int i = 0; i < FEATURES::SIZE*2; ++i)
	{
		texts.push_back(new cmm::Text);
		Loading::add(texts[i]->setFont(cmm::JAPOKKI_FONT_PATH));
		if (Loading::isError())	return;
		texts[i]->setSize(screen.y / 35);
		texts[i]->setAlpha(MAX_ALPHA);
	}

	texts[HEART_POINTS * 2]->setText("Heart Points:");
	texts[MAGIC_POINTS * 2]->setText("Magic Points:");
	texts[ARMOUR * 2]->setText("Armour:");
	texts[MAGIC_RESISTANT * 2]->setText("Magic Resistant:");
	texts[MOVEMENT_SPEED * 2]->setText("Movement Speed:");
	texts[DAMAGE * 2]->setText("Damage:");
	texts[MAGIC_DAMAGE * 2]->setText("Magic Damage:");
	texts[LUCK * 2]->setText("Luck:");
	texts[EXPERIENCE * 2]->setText("Experience:");
	texts[LEVEL * 2]->setText("Level:");
	for (int i = 1; i < FEATURES::SIZE * 2; i += 2)
		texts[i]->setText(cmm::SEMPTY);
	for (int i = 0; i < FEATURES::SIZE * 2; i += 2)
		texts[i]->setFillColor(cmm::LOCKED_COLOR);
	texts[EXPERIENCE * 2 + 1]->setText("-");
	texts[LEVEL * 2 + 1]->setText("-");
	texts[EXPERIENCE * 2 + 1]->setFillColor(cmm::LOCKED_COLOR);
	texts[LEVEL * 2 + 1]->setFillColor(cmm::LOCKED_COLOR);

	Loading::add(plus.load("images/buttons/plus.png", 3));
	if (Loading::isError())	return;
	Loading::add(minus.load("images/buttons/minus.png", 3));
	if (Loading::isError())	return;
	plus.setScale(screen.x / 3840, screen.y / 2160);
	minus.setScale(screen.x / 3840, screen.y / 2160);

	mins.resize(FEATURES::SIZE - 2); // we do not count EXPERIENCE and LEVEL
	maxs.resize(FEATURES::SIZE - 2);
	values.resize(FEATURES::SIZE - 2);
	ratios.resize(FEATURES::SIZE - 2);
	ratios[HEART_POINTS] = 0.03f;	values[HEART_POINTS] =		mins[HEART_POINTS] = 1;			maxs[HEART_POINTS] = 10000;		// points
	ratios[MAGIC_POINTS] = 0.1f;	values[MAGIC_POINTS] =		mins[MAGIC_POINTS] = 1;			maxs[MAGIC_POINTS] = 2000;		// points
	ratios[ARMOUR] = 0.1f;			values[ARMOUR] =			mins[ARMOUR] = 0;				maxs[ARMOUR] = 1000;			// per mille, 0%-100%
	ratios[MAGIC_RESISTANT] = 0.1f;	values[MAGIC_RESISTANT] =	mins[MAGIC_RESISTANT] = 0;		maxs[MAGIC_RESISTANT] = 1000;	// per mille, 0%-100%
	ratios[MOVEMENT_SPEED] = 0.25f;	values[MOVEMENT_SPEED] =	mins[MOVEMENT_SPEED] = 20;		maxs[MOVEMENT_SPEED] = 200;		// 0.2px/sec - 2.0px/sec (conventionally)
	ratios[DAMAGE] = 0.1f;			values[DAMAGE] =			mins[DAMAGE] = 0;				maxs[DAMAGE] = 1000;			// points
	ratios[MAGIC_DAMAGE] = 0.1f;	values[MAGIC_DAMAGE] =		mins[MAGIC_DAMAGE] = 0;			maxs[MAGIC_DAMAGE] = 2000;		// points
	ratios[LUCK] = 0.1f;			values[LUCK] =				mins[LUCK] = 1;					maxs[LUCK] = 50;				// percent, 1%-50%	

	rects.resize(FEATURES::EXPERIENCE * 2); // * 2 minus/plus
	states.resize(FEATURES::EXPERIENCE * 2); // * 2 minus/plus
	for (int i = 0; i < FEATURES::EXPERIENCE * 2; ++i)
	{
		rects[i].width = plus.getWidth();
		rects[i].height = plus.getHeight();
	}
}

void ee::KnightBoard::draw(sf::RenderWindow* &window)
{
	window->draw(board);

	for (auto &it : texts)
		window->draw(*it);

	for (int i = 0; i < EXPERIENCE; ++i)
	{
		states[i] ? minus.setOffset(1) : minus.setOffset(0);
		minus.setPosition(rects[i].left, rects[i].top);
		window->draw(minus);
	}

	for (int i = EXPERIENCE; i < EXPERIENCE * 2; ++i)
	{
		states[i] ? plus.setOffset(1) : plus.setOffset(0);
		plus.setPosition(rects[i].left, rects[i].top);
		window->draw(plus);
	}
}


ee::Knight::Knight()
{
	free();
}

ee::Knight::~Knight()
{
	free();
}

void ee::Knight::free()
{
	reset();
	screen.x = screen.y = 0;
}

void ee::Knight::reset()
{
	modified = false;
	item.reset();
}

bool ee::Knight::isModified()
{
	if (modified)
	{
		modified = false;
		return true;
	}

	return false;
}

//void ee::Knight::setActive(bool active)
//{
//	this->active = active;
//}

ee::Item ee::Knight::getItem()
{
	std::string new_ai = cmm::SEMPTY;
	new_ai += "hp(" + std::to_string(static_cast<int>(board.values[board.HEART_POINTS])) + "), ";
	new_ai += "mp(" + std::to_string(static_cast<int>(board.values[board.MAGIC_POINTS])) + "), ";
	new_ai += "armour(" + cmm::floatToStr(board.values[board.ARMOUR] / 1000, 3) + "), ";
	new_ai += "mr(" + cmm::floatToStr(board.values[board.MAGIC_RESISTANT] / 1000, 3) + "), ";
	new_ai += "ms(" + cmm::floatToStr(board.values[board.MOVEMENT_SPEED] / 100, 2) + "), ";
	new_ai += "dmg(" + cmm::floatToStr(board.values[board.DAMAGE], 1) + "), ";
	new_ai += "mdmg(" + cmm::floatToStr(board.values[board.MAGIC_DAMAGE], 1) + "), ";
	new_ai += "luck(" + std::to_string(static_cast<int>(board.values[board.LUCK])) + ")";
	item.ai = new_ai;

	return item;
}

bool ee::Knight::checkCollision(sf::Vector2i &mouse)
{
	rect.left = item.position.x;
	rect.top = item.position.y;

	// here I added own implementation of contains()
	// the reason: y is in correct axis where higher y values are going upwards.
	if (!wholeCollision)
	{
		if (mouse.x < rect.left)				return false;
		if (mouse.x > rect.left + rect.width)	return false;
		if (mouse.y > rect.top)					return false;
		if (mouse.y < rect.top - rect.height)	return false;
		return true;
	}
	
	sf::IntRect oblong;
	oblong.left = mouse.x;
	oblong.top = mouse.y;
	oblong.width = rect.width;
	oblong.height = rect.height;
	return rect.intersects(oblong);
}

void ee::Knight::load(sf::Vector2f &screen, int amount)
{
	free();
	this->screen = screen;

	// Load sprites. (1)
	for (int i = 0; i < amount; ++i)
	{
		sprites.push_back(new cmm::Sprite());
		Loading::add(sprites[i]->load("images/platform/knight/" + std::to_string(i) + ".png", 10));
		if (Loading::isError())	return;
		sprites[i]->setScale(0.45f, 0.45f);
		sprites[i]->setAlpha(MAX_ALPHA);
	}

	rect.width = static_cast<int>(sprites[0]->getWidth());
	rect.height = static_cast<int>(sprites[0]->getHeight());

	board.load(screen);
}

void ee::Knight::handle(const sf::Event &event)
{
	if (!active)
		return;

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2i mouse(event.mouseButton.x, event.mouseButton.y);

			for (size_t i = 0; i < board.rects.size(); ++i)
			{
				if (board.rects[i].contains(mouse))
				{
					board.states[i] = true;
					return;
				}
			}

			if (!board.board.checkCollision(mouse.x, mouse.y))
			{
				active = false;
				for (auto it : board.states)
					it = false;

				modified = true;
				return;
			}
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			for (auto it : board.states)
				it = false;
		}
	}

	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			active = false;
			modified = false;
			return;
		}
	}
}

void ee::Knight::draw(sf::RenderWindow* &window, sf::Vector2i &add)
{
	if (item.position.x != -1 && item.position.y != -1)
	{
		sprites[0]->setPosition(item.position.x + add.x, -(item.position.y + add.y) + screen.y);
		window->draw(*sprites[0]);

		if (active)
		{
			setPosition(add);
			board.draw(window);
		}
	}
}

void ee::Knight::mechanics(const double &elapsedTime)
{
	float value = elapsedTime;

	for (int i = 0; i < board.FEATURES::EXPERIENCE; ++i) // minus
	{
		if (board.states[i])
		{
			board.values[i] -= value * static_cast<float>(board.maxs[i]) * board.ratios[i];
			if (board.values[i] < static_cast<float>(board.mins[i]))
				board.values[i] = static_cast<float>(board.mins[i]);
		}
	}

	for (int i = board.EXPERIENCE; i < board.EXPERIENCE * 2; ++i) // plus
	{
		if (board.states[i])
		{
			int j = i - board.EXPERIENCE;
			board.values[j] += value * static_cast<float>(board.maxs[j]) * board.ratios[j];
			if (board.values[j] > static_cast<float>(board.maxs[j]))
				board.values[j] = static_cast<float>(board.maxs[j]);
		}
	}
}

bool ee::Knight::add(Item &data)
{
	if (!data.ai.empty() && data.ai != cmm::CSNEWLINE)
	{
		std::string str = item.ai = data.ai;
		board.values[board.HEART_POINTS] = boost::lexical_cast<float>(str.substr(str.find("hp(") + 3, str.find("), mp(") - (str.find("hp(") + 3)));
		board.values[board.MAGIC_POINTS] = boost::lexical_cast<float>(str.substr(str.find("mp(") + 3, str.find("), armour(") - (str.find("mp(") + 3)));
		board.values[board.ARMOUR] = boost::lexical_cast<float>(str.substr(str.find("armour(") + 7, str.find("), mr(") - (str.find("armour(") + 7))) * 1000;
		board.values[board.MAGIC_RESISTANT] = boost::lexical_cast<float>(str.substr(str.find("mr(") + 3, str.find("), ms(") - (str.find("mr(") + 3))) * 1000;
		board.values[board.MOVEMENT_SPEED] = boost::lexical_cast<float>(str.substr(str.find("ms(") + 3, str.find("), dmg(") - (str.find("ms(") + 3))) * 100;
		board.values[board.DAMAGE] = boost::lexical_cast<float>(str.substr(str.find("dmg(") + 4, str.find("), mdmg(") - (str.find("dmg(") + 4)));
		board.values[board.MAGIC_DAMAGE] = boost::lexical_cast<float>(str.substr(str.find("mdmg(") + 5, str.find("), luck(") - (str.find("mdmg(") + 5)));
		board.values[board.LUCK] = boost::lexical_cast<float>(str.substr(str.find("luck(") + 5, (str.size() - 1) - (str.find("luck(") + 6)));
	}
	else
		item.ai = cmm::SEMPTY;

	item.ID = data.ID;
	item.position = data.position;
	item.type = cmm::Kind::KNIGHT;
	item.chosen = data.chosen;

	return true;
}

bool ee::Knight::remove(sf::Vector2i &mouse)
{
	if (checkCollision(mouse))
	{
		item.ai = cmm::SEMPTY;
		item.position = sf::Vector2i(-1, -1);
		return true;
	}

	return false;
}

bool ee::Knight::unfold(sf::Vector2i &mouse)
{
	if (checkCollision(mouse))
	{
		setPosition(mouse);
		setActive(true);
		return true;
	}

	return false;
}



void ee::Knight::setTexts()
{
	board.texts[board.HEART_POINTS * 2 + 1]->	setText(std::to_string(static_cast<int>(board.values[board.HEART_POINTS])) + "p.");
	board.texts[board.MAGIC_POINTS * 2 + 1]->	setText(std::to_string(static_cast<int>(board.values[board.MAGIC_POINTS])) + "p.");
	board.texts[board.ARMOUR * 2 + 1]->			setText(cmm::floatToStr(board.values[board.ARMOUR] / 10, 1) + "%");
	board.texts[board.MAGIC_RESISTANT * 2 + 1]->setText(cmm::floatToStr(board.values[board.MAGIC_RESISTANT] / 10, 1) + "%");
	board.texts[board.MOVEMENT_SPEED * 2 + 1]->	setText(cmm::floatToStr(board.values[board.MOVEMENT_SPEED] / 100, 2) + "px/sec");
	board.texts[board.DAMAGE * 2 + 1]->			setText(cmm::floatToStr(board.values[board.DAMAGE], 1) + "p.");
	board.texts[board.MAGIC_DAMAGE * 2 + 1]->	setText(cmm::floatToStr(board.values[board.MAGIC_DAMAGE], 1) + "p.");
	board.texts[board.LUCK * 2 + 1]->			setText(std::to_string(static_cast<int>(board.values[board.LUCK])) + "%");

	board.texts[board.HEART_POINTS]->setPosition(board.board.getX() + screen.x / 256, board.board.getY() + screen.y / 144);
	for(int i = board.MAGIC_POINTS*2; i < board.SIZE * 2; i += 2)
		board.texts[i]->setPosition(board.texts[i - 2]->getX(), board.texts[i - 2]->getBot() + screen.y / 144);
	for (int i = board.HEART_POINTS + 1; i < board.SIZE * 2; i += 2)
		board.texts[i]->setPosition(board.texts[i - 1]->getRight() + screen.x / 256, board.texts[i - 1]->getY());
}

void ee::Knight::setRects()
{
	for (int i = 0; i < board.FEATURES::EXPERIENCE; ++i)
	{
		board.rects[i].left = board.board.getRight();
		board.rects[i].top = board.texts[i*2]->getTop() + screen.y / 144;
	}

	for (int i = board.EXPERIENCE; i < board.EXPERIENCE * 2; ++i)
	{
		board.rects[i].left = board.rects[i - board.EXPERIENCE].left + board.rects[i - board.EXPERIENCE].width;
		board.rects[i].top = board.rects[i - board.EXPERIENCE].top;
	}
}

void ee::Knight::setPosition(sf::Vector2i add)
{
	board.board.setPosition(item.position.x + add.x + sprites[0]->getWidth(), (item.position.y + add.y) * -1 + screen.y - board.board.getHeight());
	setTexts();
	setRects();
}