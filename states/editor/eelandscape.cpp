#include "eelandscape.h"
#include "loading.h"

ee::LandscapeItem::LandscapeItem(int ID, char chosen, float scale)
{
	this->ID = ID;
	this->chosen = chosen;
	type = LANDSCAPE;
	this->scale = scale;
	ai = cmm::SEMPTY;
	position = sf::Vector2i(0, 0);
}

ee::LandscapeItem::LandscapeItem(Item &it, float scale)
{
	this->ID = it.ID;
	this->chosen = it.chosen;
	type = LANDSCAPE;
	this->scale = scale;
	ai = cmm::SEMPTY;
	position = it.position;
}

ee::LandscapeItem::~LandscapeItem()
{
	scale = 0.0f;
}



void ee::LandscapeBoard::free()
{
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

	if (!states.empty())
		states.clear();
}

void ee::LandscapeBoard::load(sf::Vector2f &screen)
{
	Loading::add(board.load("images/other/splank.png"));
	if (Loading::isError())	return;

	board.setScale(screen.x / 5120, screen.y / 2880);

	for (int i = 0; i < SIZE; ++i)
	{
		texts.push_back(new cmm::Text);
		Loading::add(texts[i]->setFont(cmm::JAPOKKI_FONT_PATH));
		if (Loading::isError())	return;
		texts[i]->setSize(screen.y / 35);
		texts[i]->setAlpha(MAX_ALPHA);
	}

	texts[SCALE]->setText("Scale:");
	texts[SCALE_EDIT]->setText(cmm::SEMPTY);
	texts[GLOBAL]->setText("Global Scale:");
	texts[GLOBAL_EDIT]->setText(cmm::SEMPTY);
	texts[SCALE]->setFillColor(cmm::LOCKED_COLOR);
	texts[GLOBAL]->setFillColor(cmm::LOCKED_COLOR);

	Loading::add(plus.load("images/buttons/plus.png", 3));
	if (Loading::isError())	return;
	Loading::add(minus.load("images/buttons/minus.png", 3));
	if (Loading::isError())	return;

	plus.setScale(screen.x / 3840, screen.y / 2160);
	minus.setScale(screen.x / 3840, screen.y / 2160);

	for (int i = 0; i < SIZE; ++i)
	{
		rects.push_back(sf::Rect<int>());
		states.push_back(false);
		rects[i].width = plus.getWidth();
		rects[i].height = plus.getHeight();
	}
}

void ee::LandscapeBoard::draw(sf::RenderWindow* &window)
{
	window->draw(board);

	for (auto &it : texts)
		window->draw(*it);

	for (int i = 0; i < TOP_PLUS; ++i)
	{
		states[i] ? minus.setOffset(1) : minus.setOffset(0);
		minus.setPosition(rects[i].left, rects[i].top);
		window->draw(minus);
	}

	for (int i = TOP_PLUS; i < SIZE; ++i)
	{
		states[i] ? plus.setOffset(1) : plus.setOffset(0);
		plus.setPosition(rects[i].left, rects[i].top);
		window->draw(plus);
	}
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
	reset();

	if (!sprites.empty())
	{
		for (auto &it : sprites)
		{
			delete it;
			it = nullptr;
		}

		sprites.clear();
	}

	if (tree)
	{
		delete tree;
		tree = nullptr;
	}

	board.free();

	minScale = 0.4f;		// 40%
	maxScale = 1.0f;		// 100%
	allowDuplicates = true;
	screen = sf::Vector2f(0.0f, 0.0f);
}

void ee::Landscape::reset()
{
	item.reset();
	active = false;
	modified = false;

	if (tree)
	{
		delete tree;
		tree = new LandscapeTree;
	}

	result.clear();
}



bool ee::Landscape::isModified()
{
	if (modified)
	{
		modified = false;
		return true;
	}

	return false;
}

void ee::Landscape::setActive(bool active)
{
	this->active = active;
	if (active)
		setPosition();
}

ee::Item ee::Landscape::getItem()
{
	Item* buf = dynamic_cast<Item*> (&item);
	buf->ai = "(scale:" + cmm::floatToStr(item.scale) + ")";
	return *buf;
}

cmm::Sprite* ee::Landscape::getSprite(const int &chosen)
{
	sprites[chosen]->setScale(globalScale, globalScale);
	return sprites[chosen];
}

bool ee::Landscape::checkCollision(sf::Vector2i &mouse)
{
	result.clear();
	Box queryBox(Point(mouse.x, mouse.y), Point(mouse.x + 1, mouse.y + 1));
	tree->query(bgi::intersects(queryBox), std::back_inserter(result));
	return !result.empty();
}



void ee::Landscape::load(sf::Vector2f &screen, int amount)
{
	free();

	// Load sprites.
	for (int i = 0; i < amount; ++i)
	{
		sprites.push_back(new cmm::Sprite());
		Loading::add(sprites[i]->load("images/platform/landscape/" + std::to_string(i) + ".png"));
		if (Loading::isError())	return;
		sprites[i]->setScale(globalScale, globalScale);
		sprites[i]->setAlpha(MAX_ALPHA);
	}

	// Build tree.
	tree = new LandscapeTree;

	this->screen = screen;

	board.load(screen);
}

void ee::Landscape::handle(const sf::Event &event)
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
				ee::Item item = getItem();
				add(item);
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

void ee::Landscape::draw(sf::RenderWindow* &window, sf::Vector2i &add)
{
	result.clear();
	Box queryBox(Point(add.x, -add.y), Point(add.x + screen.x, -add.y + screen.y));
	tree->query(bgi::intersects(queryBox), std::back_inserter(result));

	int c;
	float x = 0, y = 0;
	BOOST_FOREACH(LandscapeBox const& it, result)
	{
		c = it.second.chosen;
		sprites[c]->setScale(it.second.scale, it.second.scale);
		x = bg::get<0>(it.first.min_corner()) + add.x;
		y = (bg::get<1>(it.first.max_corner()) + add.y) * -1 + screen.y;
		sprites[c]->setPosition(x, y);
		window->draw(*sprites[c]);
	}

	if (!active)
		return;

	//if (item.ID != item.VOID)
	{
		sprites[item.chosen]->setScale(item.scale, item.scale);

		float tX = item.position.x + add.x;
		float tY = (item.position.y + add.y) * -1 + screen.y;

		sprites[item.chosen]->setPosition(tX, tY);
		sprites[item.chosen]->setColor(cmm::GREEN_COLOR);
		window->draw(*sprites[item.chosen]);
		sprites[item.chosen]->setColor(cmm::LOADING_COLOR);	// set back
	}

	setPosition(add);
	board.draw(window);
}

void ee::Landscape::mechanics(const double &elapsedTime)
{
	if (!active)
		return;

	float value = elapsedTime;

	if (board.states[board.TOP_MINUS])
	{
		item.scale -= value;
		if (item.scale < minScale)
			item.scale = minScale;
	}
	else if (board.states[board.TOP_PLUS])
	{
		item.scale += value;
		if (item.scale > maxScale)
			item.scale = maxScale;
	}
	else if (board.states[board.BOT_MINUS])
	{
		globalScale -= value;
		if (globalScale < minScale)
			globalScale = minScale;
	}
	else if (board.states[board.BOT_PLUS])
	{
		globalScale += value;
		if (globalScale > maxScale)
			globalScale = maxScale;
	}
}

bool ee::Landscape::add(Item &data)
{
	LandscapeLeaf ll;
	if (data.ai.empty() || data.ai == cmm::CSNEWLINE)
		ll.scale = globalScale;
	else
		ll.scale = boost::lexical_cast<float>(cmm::extractFromString(data.ai, "(scale:", ')'));
	ll.chosen = data.chosen;
	ll.ID = data.ID;

	sprites[data.chosen]->setScale(ll.scale, ll.scale);
	int w = sprites[data.chosen]->getWidth();
	int h = sprites[data.chosen]->getHeight();

	// If item was modified it means we add the item back, so its position is already set correctly.
	Box box(Point(data.position.x, data.position.y + (modified ? -h : 0)), Point(data.position.x + w, data.position.y + (modified ? 0 : h)));
	data.position = sf::Vector2i(data.position.x, data.position.y);

	item = ee::LandscapeItem(data, ll.scale);
	tree->insert(std::make_pair(box, ll));
	return true;
}

bool ee::Landscape::remove(sf::Vector2i &mouse)
{
	if (checkCollision(mouse))
	{
		mouse.x = bg::get<0>(result[0].first.min_corner());
		mouse.y = bg::get<1>(result[0].first.max_corner());
		item.ID = result[0].second.ID;
		tree->remove(result[0]);
		return true;
	}

	return false;
}

bool ee::Landscape::unfold(sf::Vector2i &mouse)
{
	if (checkCollision(mouse))
	{
		float x = bg::get<0>(result[0].first.min_corner());
		float y = bg::get<1>(result[0].first.max_corner());
		item.position = sf::Vector2i(static_cast<int>(x), static_cast<int>(y));
		item.chosen = result[0].second.chosen;
		setActive(true);
		tree->remove(result[0]);
		return true;
	}

	return false;
}



void ee::Landscape::setTexts()
{
	board.texts[board.SCALE_EDIT]->		setText(std::to_string(static_cast<int>(item.scale * 100)) + "%");
	board.texts[board.GLOBAL_EDIT]->	setText(std::to_string(static_cast<int>(globalScale * 100)) + "%");
	board.texts[board.SCALE]->			setPosition(board.board.getX() + screen.x / 256, board.board.getY() + screen.y / 144);
	board.texts[board.GLOBAL]->			setPosition(board.texts[board.SCALE]->getX(), board.texts[board.SCALE]->getBot() + screen.y / 144);
	board.texts[board.SCALE_EDIT]->		setPosition(board.texts[board.GLOBAL]->getRight() + screen.x / 256,	board.texts[board.SCALE]->getY());
	board.texts[board.GLOBAL_EDIT]->	setPosition(board.texts[board.GLOBAL]->getRight() + screen.x / 256, board.texts[board.GLOBAL]->getY());
}

void ee::Landscape::setRects()
{
	board.rects[board.TOP_MINUS].left =		board.board.getRight();
	board.rects[board.TOP_MINUS].top =		board.texts[board.SCALE]->getTop() + screen.y / 144;
	board.rects[board.TOP_PLUS].left =		board.rects[board.TOP_MINUS].left + board.rects[board.TOP_MINUS].width;
	board.rects[board.TOP_PLUS].top =		board.rects[board.TOP_MINUS].top;

	board.rects[board.BOT_MINUS].left =		board.rects[board.TOP_MINUS].left;
	board.rects[board.BOT_MINUS].top =		board.texts[board.GLOBAL]->getTop() + screen.y / 144;
	board.rects[board.BOT_PLUS].left =		board.rects[board.TOP_PLUS].left;
	board.rects[board.BOT_PLUS].top =		board.rects[board.BOT_MINUS].top;
}

void ee::Landscape::setPosition(sf::Vector2i add)
{
	board.board.setPosition(item.position.x + add.x, (item.position.y + add.y) * -1 + screen.y - board.board.getHeight());
	setTexts();
	setRects();
}