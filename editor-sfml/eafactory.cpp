#include "eafactory.h"
#include "state.h"

EAFactory::EAFactory()
{
	free();
}

EAFactory::~EAFactory()
{
	free();
}

void EAFactory::free()
{
	width = screen_w = screen_h = 0;

	reset();

	if (!amounts.empty())
		amounts.clear();

	if (!factory.empty())
	{
		for(auto &it : factory)
		{
			if (!it.empty())
			{
				for (auto &jt : it)
				{
					delete jt;
					jt = nullptr;
				}

				it.clear();
			}
		}

		factory.clear();
		factory.shrink_to_fit();
	}
}

void EAFactory::reset()
{
	type = VOID;
	chosen = 0;
	change = false;
	redBacklight = false;
	tools.reset();
}


void EAFactory::load(const float& screen_w, const float& screen_h)
{
	free();

	this->screen_w = screen_w;
	this->screen_h = screen_h;
	float scale = 0.51f;

	// Knight
	amounts.push_back(1);
	factory.push_back(std::vector<cmm::Sprite*>());
	factory[KNIGHT].push_back(new cmm::Sprite());
	factory[KNIGHT][0]->load("images/platform/knight/0.png", 10);
	factory[KNIGHT][0]->setScale(scale, scale);

	// Tile
	amounts.push_back(21);
	factory.push_back(std::vector<cmm::Sprite*>());
	for (int i = 0; i < amounts[TILE]; ++i)
	{
		factory[TILE].push_back(new cmm::Sprite());
		factory[TILE][i]->load("images/platform/tiles/" + std::to_string(i) + ".png");
		factory[TILE][i]->setScale(scale, scale);
	}

	// Unvisible Tile
	amounts.push_back(21);
	factory.push_back(std::vector<cmm::Sprite*>());

	// Landscape
	amounts.push_back(14);
	factory.push_back(std::vector<cmm::Sprite*>());
	for (int i = 0; i < amounts[LANDSCAPE]; ++i)
	{
		factory[LANDSCAPE].push_back(new cmm::Sprite());
		factory[LANDSCAPE][i]->load("images/platform/landscape/" + std::to_string(i) + ".png");
		factory[LANDSCAPE][i]->setScale(scale, scale);
	}

	// Foes
	amounts.push_back(2);
	factory.push_back(std::vector<cmm::Sprite*>());
	for (int i = 0; i < amounts[FOE]; ++i)
	{
		factory[FOE].push_back(new cmm::Sprite());
		factory[FOE][i]->load("images/platform/foes/type/thumbnails/" + std::to_string(i) + ".png");
		factory[FOE][i]->setScale(scale, scale);
	}

	tools.load(screen_w, screen_h);

	width = 32;	// 64 is the width of a single tile but we divide it
	entityKnight.init(factory[KNIGHT][0]->getWidth(), factory[KNIGHT][0]->getHeight());
	entityTiles.init(width);
	entityUnTiles.init(width);
	entityLandscape.init();
}

bool EAFactory::handle(const sf::Event &event, const int &addX, const int &addY)
{
	if (tools.handle(event))
	{
		type = VOID;
		chosen = 0;
		change = true;
	}

	if (type != VOID)
	{
		if (event.type == sf::Event::MouseWheelMoved)
		{
			float m = event.mouseWheel.delta;
			if (m < 0)
			{
				if (chosen < amounts[type] - 1)
				{
					++chosen;
					change = true;
				}
			}
			else
			{
				if (chosen > 0)
				{
					--chosen;
					change = true;
				}
			}
		}

		if (event.type == sf::Event::MouseMoved)
		{
			int mouseX = event.mouseMove.x + (addX * -1);
			int mouseY = event.mouseMove.y * -1 + screen_h + (addY * -1);
			redBacklight = !isCellEmpty(mouseX, mouseY);
		}
	}

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			int mouseX = event.mouseButton.x + (addX * -1);
			int mouseY = event.mouseButton.y * -1 + screen_h + (addY * -1);

			redBacklight = !isCellEmpty(mouseX, mouseY);
			if (!redBacklight)	// remove/add
				tools.isDeleteMode() ? remove(mouseX, mouseY) : add(mouseX, mouseY, type, chosen);
		}
		else if (event.mouseButton.button == sf::Mouse::Right)
		{
			int mouseX = event.mouseButton.x + (addX * -1);
			int mouseY = event.mouseButton.y * -1 + screen_h + (addY * -1);

			redBacklight = !isCellEmpty(mouseX, mouseY);
			if (!redBacklight)	// add
			{
				// showInfo(mouseX, mouseY);
			}
		}
	}

	if (event.type == sf::Event::KeyPressed)
	{
		int code = event.key.code;

		change = true;

		if (tools.isKeyPressed())
		{
			type = VOID;
			chosen = 0;
		}
		else if (code == sf::Keyboard::Escape)
		{
			reset();
			change = true;
			tools.resetDeleteMode();
		}
		else if (!tools.isDeleteMode())
		{
			// CHANGING CHOSEN
			if (code == sf::Keyboard::Z && chosen > 0)
				--chosen;
			else if (code == sf::Keyboard::X && chosen != 0)
				chosen /= 2;
			else if (code == sf::Keyboard::C && type != VOID && chosen < amounts[type] - 1)
				++chosen;

			// CHANGING TYPE
			else if (code == sf::Keyboard::A && type > VOID)
			{
				--type;
				chosen = 0;
			}
			else if (code == sf::Keyboard::S)
			{
				type = VOID;
				chosen = 0;
			}
			else if (code == sf::Keyboard::D && type < AMOUNT)
			{
				++type;
				chosen = 0;
			}
			else
				change = false;
		}
	}

	history.handle(event);

	return change;
}

void EAFactory::draw(sf::RenderWindow* &window, const int &addX, const int &addY)
{
	int t = type != UNVISIBLE_TILE ? type : TILE;
	float tempX, tempY;
	if (t != VOID)
	{
		tempX = factory[t][chosen]->getX();
		tempY = factory[t][chosen]->getY();
	}

	drawPrivate(window, addX, addY);

	if (type != VOID)
	{
		redBacklight ? factory[t][chosen]->setColor(User::getErrorColor()) : factory[t][chosen]->setColor(sf::Color::White);
		type == UNVISIBLE_TILE ? factory[t][chosen]->setAlpha(0xFF / 2) : factory[t][chosen]->setAlpha(0xFF);
		factory[t][chosen]->setPosition(tempX, tempY);
		window->draw(factory[t][chosen]->get());
		if (redBacklight)			factory[t][chosen]->setColor(sf::Color::White);	// set back
		if(type == UNVISIBLE_TILE)	factory[t][chosen]->setAlpha(0xFF);				// set back
		tools.draw(window, factory[t], chosen);
	}

	tools.drawTools(window);
}

void EAFactory::mechanics()
{
	int t, x, y;
	if (history.undo(t, x, y))
	{
		if (t == KNIGHT)					entityKnight.remove(x, y);
		else if (t == TILE)					entityTiles.remove(x, y);
		else if (t == UNVISIBLE_TILE)		entityUnTiles.remove(x, y);
		else if (t == LANDSCAPE)			entityLandscape.remove(x, y);
		else if (t == FOE) {}
		else if (t == LIGHTPOINT) {}
	}

	if (history.isNewLoadVersion())	// clear everything and reload it
	{
		history.clear_local();
		history.fill_local();

		entityKnight.reset();
		entityTiles.reset();
		entityUnTiles.reset();
		entityLandscape.reset();	entityLandscape.init();

		char t, c;
		int x, y, id;
		std::string ai;
		while (history.next())
		{
			history.getTC(t, c);
			history.getXY(x, y);
			history.getID(id);
			history.getAI(ai);

			add(x, y, t, c, id, ai, true);
		}
	}
}



void EAFactory::setPosition(float x, float y)
{
	if (type == VOID)
		return;

	int t = type != UNVISIBLE_TILE ? type : TILE;
	factory[t][chosen]->setPosition(x, y);
}

bool EAFactory::isChange()
{
	if (change)
	{
		change = false;
		return true;
	}

	return false;
}

bool EAFactory::isDeleteMode()
{
	return tools.isDeleteMode();
}

const int& EAFactory::getType() const
{
	return type;
}

const int& EAFactory::getChosen() const
{
	return chosen;
}




void EAFactory::drawPrivate(sf::RenderWindow* &window, const int &addX, const int &addY)
{
	// Draw knight
	if (entityKnight.isSet())
	{
		factory[KNIGHT][0]->setPosition(entityKnight.get().x + addX, (entityKnight.get().y + addY + factory[KNIGHT][0]->getHeight()) * -1 + screen_h);
		window->draw(factory[KNIGHT][0]->get());
	}
	
	// log(1) time
	int startX = -addX / width;
	int endX = -addX + screen_w / width;
	int startY = -addY / width;
	int endY = -addY + screen_h / width;
	char c;
	for (int i = startX; i < endX; ++i)
	{
		for (int j = startY; j < endY; ++j)
		{
			c = entityTiles.get(i, j);		// Draw tiles
			if (c != VOID)
			{
				factory[TILE][c]->setPosition(i * width + addX, ((j * width + addY) * -1) + screen_h - width);
				window->draw(factory[TILE][c]->get());
			}

			c = entityUnTiles.get(i, j);	// Draw Unvisible Tiles
			if (c != VOID)
			{
				factory[TILE][c]->setAlpha(0xFF / 2);
				factory[TILE][c]->setPosition(i * width, (j * width * -1) + screen_h - width);
				window->draw(factory[TILE][c]->get());
				factory[TILE][c]->setAlpha(0xFF);	// set back
			}
		}
	}

	// Draw Landscape
	float x = 0, y = 0;
	std::vector<EntityRectID> result = entityLandscape.get(-addX, -addY, screen_w, screen_h);
	BOOST_FOREACH(EntityRectID const& item, result)
	{
		c = char(item.second.second);
		x = bg::get<0>(item.first.min_corner()) + addX;
		y = (bg::get<1>(item.first.min_corner()) + addY + factory[LANDSCAPE][c]->getHeight()) * -1 + screen_h;
		factory[LANDSCAPE][c]->setPosition(x, y);
		window->draw(factory[LANDSCAPE][c]->get());
	}
}

bool EAFactory::isCellEmpty(const int& x, const int& y)
{
	if (type == TILE || type == UNVISIBLE_TILE)
	{
		if (!entityTiles.isCellEmpty(x, y))
			return false;
	}

	return true;
}

void EAFactory::add(int& x, int& y, int t, int c, int id, std::string ai, bool con)
{
	if (t == VOID)
		return;

	bool success = false;
	int newID = id;
	if (t == KNIGHT)
	{
		if(id == -1)	newID = history.getNewID();
		if(!con)	y -= factory[KNIGHT][0]->getHeight();
		success = entityKnight.add(x, y, newID);
	}
	else if (t == TILE)				success = entityTiles.add(x, y, c);
	else if (t == UNVISIBLE_TILE)	success = entityUnTiles.add(x, y, c);
	else if (t == LANDSCAPE)
	{
		if (id == -1)	newID = history.getNewID();
		Box box(Point(x, y - factory[LANDSCAPE][c]->getHeight()), Point(x + factory[LANDSCAPE][c]->getWidth(), y));
		IDPair idpair = std::make_pair(newID, c);
		success = entityLandscape.add(box, idpair);
	}
	else if (t == FOE) {}
	else if (t == LIGHTPOINT) {}

	if(success && !con)
		history.add(t, c, x, y, ai, newID);
}

void EAFactory::remove(int& x, int& y)
{
	int c = 0;
	if (entityKnight.remove(x, y))					history.removeByID(entityKnight.getID());
	else if (c = entityTiles.remove(x, y) != -1)	history.remove(TILE, c, x, y);
	else if (c = entityUnTiles.remove(x, y) != -1)	history.remove(UNVISIBLE_TILE, c, x, y);
	else if (entityLandscape.remove(x, y))			history.removeByID(entityLandscape.getID());
	else if (type == FOE) {}
	else if (type == LIGHTPOINT) {}
}