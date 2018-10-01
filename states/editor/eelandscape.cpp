#include "eelandscape.h"
#include "logconsole.h"
#include "loading.h"

ee::LandscapeEntity::LandscapeEntity(int newID, int newChosen, float newScale)
: id(newID), chosen(newChosen), scale(newScale)
{
	// ...
}

ee::LandscapeEntity::~LandscapeEntity()
{
	id = -1;
	chosen = -1;
	scale = 0.0f;
}

bool ee::LandscapeEntity::operator==(const LandscapeEntity &le) const
{
	return id == le.id;
}


ee::Landscape::Landscape()
{
	tree = nullptr;
	free();
}

ee::Landscape::~Landscape()
{
	free();
}

void ee::Landscape::free()
{
	screen_w = screen_h = 0;

	if (!texts.empty())
	{
		for (auto &it : texts)
		{
			delete it;
			it = nullptr;
		}

		texts.clear();
	}

	if (!rects.empty())
		rects.clear();

	min = 0.4f; // 40%
	max = 1.0f; // 100%

	reset();
}

void ee::Landscape::reset()
{
	last.second.id = -1;

	active = false;
	str = "";
	w = h = 0;

	if (tree)
	{
		delete tree;
		tree = nullptr;
	}
}

void ee::Landscape::init()
{
	reset();
	tree = new LandscapeTree;
}

void ee::Landscape::load(const float &screen_w, const float &screen_h)
{
	free();
	init();

	this->screen_w = screen_w;
	this->screen_h = screen_h;

	Loading::add(board.load("images/other/splank.png"));
	if (Loading::isError())	return;
	board.setScale(screen_w / 5120, screen_h / 2880);

	for (int i = 0; i < SIZE; ++i)
	{
		texts.push_back(new cmm::Text);
		Loading::add(texts[i]->setFont(cmm::JAPOKKI_FONT_PATH));
		if (Loading::isError())	return;
		texts[i]->setSize(screen_h / 35);
		texts[i]->setAlpha(0xFF);
	}
	texts[SCALE]->setText("Scale:");
	texts[SCALE_EDIT]->setText("");
	texts[GLOBAL]->setText("Global Scale:");
	texts[GLOBAL_EDIT]->setText("");
	texts[SCALE]->setFillColor(cmm::LogConsole::getLockedColor());
	texts[GLOBAL]->setFillColor(cmm::LogConsole::getLockedColor());

	Loading::add(plus.load("images/buttons/plus.png", 3));
	Loading::add(minus.load("images/buttons/minus.png", 3));
	if (Loading::isError())	return;
	plus.setScale(screen_w / 3840, screen_h / 2160);
	minus.setScale(screen_w / 3840, screen_h / 2160);

	for (int i = 0; i < SIZE; ++i)
	{
		rects.push_back(sf::Rect<int>());
		rect_states.push_back(false);
		rects[i].width = plus.getWidth();
		rects[i].height = plus.getHeight();
	}
}

bool ee::Landscape::handle(const sf::Event &event)
{
	if (!active)
		return false;

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2i mouse(event.mouseButton.x, event.mouseButton.y);

			for (size_t i = 0; i < rects.size(); ++i)
			{
				if (rects[i].contains(mouse))
				{
					rect_states[i] = true;
					return false;
				}
			}

			if (!board.checkCollision(mouse.x, mouse.y))
			{
				active = false;
				for (auto it : rect_states)
					it = false;

				tree->insert(last);
				active = false;
				return true;
			}
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			for (auto it : rect_states)
				it = false;
		}
	}

	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			tree->insert(last);
			active = false;
			return true;
		}
	}

	return false;
}

void ee::Landscape::draw(sf::RenderWindow* &window, cmm::Sprite* &object, const int &addX, const int &addY)
{
	if (!active)
		return;

	setPosition(addX, addY);

	window->draw(board);

	for (auto &it : texts)
		window->draw(*it);

	for (int i = 0; i < TOP_PLUS; ++i)
	{
		rect_states[i] ? minus.setOffset(1) : minus.setOffset(0);
		minus.setPosition(rects[i].left, rects[i].top);
		window->draw(minus);
	}

	for (int i = TOP_PLUS; i < SIZE; ++i)
	{
		rect_states[i] ? plus.setOffset(1) : plus.setOffset(0);
		plus.setPosition(rects[i].left, rects[i].top);
		window->draw(plus);
	}

	object->setScale(last.second.scale, last.second.scale);
	float tX = bg::get<0>(last.first.min_corner()) + addX;
	float tY = (bg::get<1>(last.first.min_corner()) + addY + object->getHeight()) * -1 + screen_h;
	object->setPosition(tX, tY);
	object->setColor(sf::Color::Yellow);
	window->draw(*object);
	object->setColor(sf::Color::White);	// set back
}

void ee::Landscape::mechanics(const double &elapsedTime)
{
	if (!active)
		return;

	float value = elapsedTime;
	bool change = true;

	if (rect_states[TOP_MINUS])
	{
		last.second.scale -= value;
		if (last.second.scale < min)
			last.second.scale = min;
	}
	else if (rect_states[TOP_PLUS])
	{
		last.second.scale += value;
		if (last.second.scale > max)
			last.second.scale = max;
	}
	else if (rect_states[BOT_MINUS])
	{
		globalScale -= value;
		if (globalScale < min)
			globalScale = min;
	}
	else if (rect_states[BOT_PLUS])
	{
		globalScale += value;
		if (globalScale > max)
			globalScale = max;
	}
	else
		change = false;

	if (change)
	{
		int tX = bg::get<0>(last.first.min_corner());
		int tY = bg::get<1>(last.first.min_corner());
		Box newBox(Point(tX, tY), Point(tX + w * last.second.scale, tY + h * last.second.scale));
		last.first = newBox;
		setTexts();
	}
}



const std::vector<ee::LandscapeBox> &ee::Landscape::get(const int &addX, const int &addY, const float &screen_w, const float &screen_h)
{
	result.clear();
	Box queryBox(Point(addX, addY), Point(addX + screen_w, addY + screen_h));
	tree->query(bgi::intersects(queryBox), std::back_inserter(result));
	return result;
}

bool ee::Landscape::add(const Box &box, const LandscapeEntity &le)
{
	last = std::make_pair(box, le);
	tree->insert(last);
	return true;
}

bool ee::Landscape::remove(int &mouseX, int &mouseY)
{
	result.clear();
	Box queryBox(Point(mouseX, mouseY), Point(mouseX + 1, mouseY + 1));
	tree->query(bgi::intersects(queryBox), std::back_inserter(result));
	
	if (!result.empty())
	{
		mouseX = bg::get<0>(result[0].first.min_corner());
		mouseY = bg::get<1>(result[0].first.min_corner());
		tree->remove(result[0]);
		last = result[0];

		// set oryginal 100% width and height
		w = (bg::get<0>(last.first.max_corner()) - bg::get<0>(last.first.min_corner())) / last.second.scale;
		h = (bg::get<1>(last.first.max_corner()) - bg::get<1>(last.first.min_corner())) / last.second.scale;
		return true;
	}
	
	return false;
}



const int& ee::Landscape::getLastID()
{
	return last.second.id;
}

ee::LandscapeBox ee::Landscape::getLast()
{
	return last;
}

void ee::Landscape::setPosition(const int addX, const int addY)
{
	board.setPosition(bg::get<0>(last.first.min_corner()) + addX, (bg::get<1>(last.first.min_corner()) + addY) * -1 + screen_h);
	setTexts();
	setRects();
}

void ee::Landscape::setTexts()
{
	texts[SCALE_EDIT]->setText(std::to_string(static_cast<int>(last.second.scale * 100)) + "%");
	texts[GLOBAL_EDIT]->setText(std::to_string(static_cast<int>(globalScale * 100)) + "%");
	texts[SCALE]->setPosition(board.getX() + screen_w / 256, board.getY() + screen_h / 144);
	texts[SCALE_EDIT]->setPosition(texts[SCALE]->getRight() + screen_w / 256, texts[SCALE]->getY());
	texts[GLOBAL]->setPosition(texts[SCALE]->getX(), texts[SCALE]->getBot() + screen_h / 144);
	texts[GLOBAL_EDIT]->setPosition(texts[GLOBAL]->getRight() + screen_w / 256, texts[GLOBAL]->getY());
}

void ee::Landscape::setRects()
{
	rects[TOP_MINUS].left = board.getRight();
	rects[TOP_MINUS].top = texts[SCALE]->getTop() + screen_h / 144;
	rects[TOP_PLUS].left = rects[TOP_MINUS].left + rects[TOP_MINUS].width;
	rects[TOP_PLUS].top = rects[TOP_MINUS].top;

	rects[BOT_MINUS].left = rects[TOP_MINUS].left;
	rects[BOT_MINUS].top = texts[GLOBAL]->getTop() + screen_h / 144;
	rects[BOT_PLUS].left = rects[TOP_PLUS].left;
	rects[BOT_PLUS].top = rects[BOT_MINUS].top;
}



void ee::Landscape::setActive(bool newActive)
{
	active = newActive;
	if (active)
	{
		setPosition();
	}
}

const bool& ee::Landscape::isActive() const
{
	return active;
}

const int& ee::Landscape::getChosen()
{
	return last.second.chosen;
}

void ee::Landscape::setAI(std::string &ai)
{
	if (ai.empty())
	{
		ai = "(scale:" + cmm::LogConsole::floatToStr(last.second.scale) + ")";
	}
}