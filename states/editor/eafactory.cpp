#include "eafactory.h"
#include "logconsole.h"
#include "loading.h"
#include "boost/scope_exit.hpp"
#include "core.h" // static core

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
	history.reset();
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
	Loading::add(factory[KNIGHT][0]->load("images/platform/knight/0.png", 10));
	if (Loading::isError())	return;
	factory[KNIGHT][0]->setScale(0.45f, 0.45f);

	// Tile
	amounts.push_back(21);
	factory.push_back(std::vector<cmm::Sprite*>());
	for (int i = 0; i < amounts[TILE]; ++i)
	{
		factory[TILE].push_back(new cmm::Sprite());
		Loading::add(factory[TILE][i]->load("images/platform/tiles/" + std::to_string(i) + ".png"));
		if (Loading::isError())	return;
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
		Loading::add(factory[LANDSCAPE][i]->load("images/platform/landscape/" + std::to_string(i) + ".png"));
		if (Loading::isError())	return;
		factory[LANDSCAPE][i]->setScale(ee::Landscape::getGlobalScale(), ee::Landscape::getGlobalScale());
	}

	// Foes
	amounts.push_back(2);
	factory.push_back(std::vector<cmm::Sprite*>());
	for (int i = 0; i < amounts[FOE]; ++i)
	{
		factory[FOE].push_back(new cmm::Sprite());
		Loading::add(factory[FOE][i]->load("images/platform/foes/type/thumbnails/" + std::to_string(i) + ".png"));
		if (Loading::isError())	return;
		factory[FOE][i]->setScale(scale, scale);
	}

	tools.load(screen_w, screen_h);

	width = 32;	// 64 is the width of a single tile but we divide it
	eKnight.init(factory[KNIGHT][0]->getWidth(), factory[KNIGHT][0]->getHeight());
	eTiles.init(width);
	eUnTiles.init(width);
	eLandscape.load(screen_w, screen_h);
}

bool EAFactory::handle(const sf::Event &event, const int &addX, const int &addY)
{
	// Delete button
	if (tools.handle(event))
	{
		type = VOID;
		chosen = 0;
		change = true;
	}

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Right)
		{
			int mouseX = event.mouseButton.x + (addX * -1);
			int mouseY = event.mouseButton.y * -1 + screen_h + (addY * -1);

			redBacklight = !checkCollision(mouseX, mouseY);
			if (!redBacklight)	// add
			{
				unfold(mouseX, mouseY);
			}
		}
	}

	// if one deck is active then return false
	if(handle_deck(event))
		return false;

	// scroll
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
	}

	bool pressed = false;
	if (tools.isHotKeyPressed())
	{
		if (type == TILE || type == UNVISIBLE_TILE || tools.isDeleteMode())
			pressed = true;
		else if (tools.isHotKeyElapsed())
			pressed = true;

	}
	else if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			pressed = true;
		}
	}

	sf::Vector2i mouse = cmm::StaticCore::getMousePosition();
	int mouseX = mouse.x + (addX * -1);
	int mouseY = mouse.y * -1 + screen_h + (addY * -1);

	redBacklight = !checkCollision(mouseX, mouseY);
	if (pressed && !redBacklight)	// remove/add
	{
		tools.isDeleteMode() ? remove(mouseX, mouseY) : add(mouseX, mouseY, type, chosen);
	}

	if (event.type == sf::Event::KeyPressed)
	{
		int code = event.key.code;

		change = true;

		if (tools.isDeleteKeyPressed())
		{
			type = VOID;
			chosen = 0;
		}
		else if (code == sf::Keyboard::Escape)
		{
			reset();
			change = true;
			tools.resetButtons();
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
		redBacklight ? factory[t][chosen]->setColor(cmm::LogConsole::getErrorColor()) : factory[t][chosen]->setColor(sf::Color::White);
		type == UNVISIBLE_TILE ? factory[t][chosen]->setAlpha(0xFF / 2) : factory[t][chosen]->setAlpha(0xFF);
		factory[t][chosen]->setPosition(tempX, tempY);

		if(t == LANDSCAPE) // set current global scale for landscape
			factory[t][chosen]->setScale(ee::Landscape::getGlobalScale(), ee::Landscape::getGlobalScale());

		window->draw(*factory[t][chosen]);

		if (redBacklight)			factory[t][chosen]->setColor(sf::Color::White);	// set back
		if(type == UNVISIBLE_TILE)	factory[t][chosen]->setAlpha(0xFF);				// set back

		tools.draw(window, factory[t], chosen);
	}

	tools.drawTools(window);
}

void EAFactory::mechanics(const double &elapsedTime)
{
	int t, x, y;
	if (history.undo(t, x, y))
	{
		if (t == KNIGHT)					eKnight.remove(x, y);
		else if (t == TILE)					eTiles.remove(x, y);
		else if (t == UNVISIBLE_TILE)		eUnTiles.remove(x, y);
		else if (t == LANDSCAPE)			eLandscape.remove(x, y);
		else if (t == FOE) {}
		else if (t == LIGHTPOINT) {}
	}

	if (history.isNewLoadVersion())	// clear everything and reload it
	{
		history.clear_local();
		history.fill_local();

		eKnight.reset();
		eTiles.reset();
		eUnTiles.reset();
		eLandscape.init();

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

	tools.mechanics(elapsedTime);
	mechanics_deck(elapsedTime);
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
	if (eKnight.isSet())
	{
		factory[KNIGHT][0]->setPosition(eKnight.get().x + addX, (eKnight.get().y + addY) * -1 + screen_h);
		window->draw(*factory[KNIGHT][0]);
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
			c = eTiles.get(i, j);		// Draw tiles
			if (c != VOID)
			{
				factory[TILE][c]->setPosition(i * width + addX, ((j * width + addY) * -1) + screen_h - width);
				window->draw(*factory[TILE][c]);
			}

			c = eUnTiles.get(i, j);	// Draw Unvisible Tiles
			if (c != VOID)
			{
				factory[TILE][c]->setAlpha(0xFF / 2);
				factory[TILE][c]->setPosition(i * width, (j * width * -1) + screen_h - width);
				window->draw(*factory[TILE][c]);
				factory[TILE][c]->setAlpha(0xFF);	// set back
			}
		}
	}

	// Draw Landscape
	float x = 0, y = 0;
	std::vector<ee::LandscapeBox> result = eLandscape.get(-addX, -addY, screen_w, screen_h);
	BOOST_FOREACH(ee::LandscapeBox const& item, result)
	{
		c = char(item.second.chosen);
		factory[LANDSCAPE][c]->setScale(item.second.scale, item.second.scale);
		x = bg::get<0>(item.first.min_corner()) + addX;
		y = (bg::get<1>(item.first.min_corner()) + addY + factory[LANDSCAPE][c]->getHeight()) * -1 + screen_h;
		factory[LANDSCAPE][c]->setPosition(x, y);
		window->draw(*factory[LANDSCAPE][c]);
	}

	// Draw decks
	eLandscape.draw(window, factory[LANDSCAPE][eLandscape.getChosen()], addX, addY);
}

bool EAFactory::checkCollision(const int& x, const int& y)
{
	sf::Rect<int> rect(x, y, 0, 0);

	if (type == TILE || type == UNVISIBLE_TILE)
	{
		rect.width = factory[TILE][0]->getWidth();
		rect.height = rect.width;
		if (eTiles.checkCollision(rect) || eUnTiles.checkCollision(rect))
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
		if(!con)
		history.removeByID(eKnight.getID());	// check if knight was added before if yes then delete him
		success = eKnight.add(x, y, newID);
	}
	else if (t == TILE)				success = eTiles.add(x, y, c);
	else if (t == UNVISIBLE_TILE)	success = eUnTiles.add(x, y, c);
	else if (t == LANDSCAPE)
	{
		if (id == -1)	newID = history.getNewID();
		float scale = ee::Landscape::getGlobalScale();
		if(!ai.empty())
			scale = boost::lexical_cast<float>(ai.substr(ai.find("scale:") + 6, ai.find(")") - (ai.find("scale:") + 6)));
		factory[LANDSCAPE][c]->setScale(scale, scale);
		Box box(Point(x, y - factory[LANDSCAPE][c]->getHeight()), Point(x + factory[LANDSCAPE][c]->getWidth(), y));
		ee::LandscapeEntity le(newID, c, scale);
		success = eLandscape.add(box, le);
		eLandscape.setAI(ai);
	}
	else if (t == FOE) {}
	else if (t == LIGHTPOINT) {}

	if(success && !con)
		history.add(t, c, x, y, ai, newID);
}

void EAFactory::remove(int& x, int& y)
{
	
	if (eKnight.remove(x, y + factory[KNIGHT][0]->getHeight()))	history.removeByID(eKnight.getID());
	else if (eLandscape.remove(x, y))							history.removeByID(eLandscape.getLastID());
	else if (type == FOE) {}
	else if (type == LIGHTPOINT) {}
	else
	{
		int c = 0;	// chosen
		if (c = eTiles.remove(x, y) != -1)			history.remove(TILE, c, x, y);
		else if (c = eUnTiles.remove(x, y) != -1)	history.remove(UNVISIBLE_TILE, c, x, y);
	}
}

void EAFactory::unfold(int& x, int& y)
{
	std::string newAI = "";

	if (eLandscape.isActive())
	{
		ee::LandscapeBox box = eLandscape.getLast();
		eLandscape.add(box.first, box.second);
		eLandscape.setAI(newAI);
		history.add(LANDSCAPE, box.second.chosen, bg::get<0>(box.first.min_corner()), bg::get<1>(box.first.min_corner()), newAI, box.second.id);
	}

	if (eLandscape.remove(x, y))
	{
		eLandscape.setActive();
		history.removeByID(eLandscape.getLastID());
	}
}

bool EAFactory::handle_deck(const sf::Event &event)
{
	bool ret_code = false;
	BOOST_SCOPE_EXIT(&ret_code, &type, &chosen)
	{
		if (ret_code)
		{
			type = VOID;
			chosen = 0;
		}
	} BOOST_SCOPE_EXIT_END;

	if (eLandscape.handle(event))
	{
		ee::LandscapeBox box = eLandscape.getLast();
		std::string newAI = "";
		eLandscape.setAI(newAI);
		history.add(LANDSCAPE, box.second.chosen, bg::get<0>(box.first.min_corner()), bg::get<1>(box.first.min_corner()), newAI, box.second.id);
	}

	if (eLandscape.isActive())
		ret_code = true;

	return ret_code;
}

void EAFactory::mechanics_deck(const double &elapsedTime)
{
	eLandscape.mechanics(elapsedTime);
}