#include "eafactory.h"
#include "loading.h"
#include "boost/scope_exit.hpp"
#include "core.h" // static core
#include "definitions.h"

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
	reset();

	if (!amounts.empty())
		amounts.clear();

	for (auto &it : entities)
	{
		delete it;
		it = nullptr;
	}

	entities.clear();
}

void EAFactory::reset()
{
	current = sf::Vector2f(0.0f, 0.0f);

	tools.reset();

	for (auto &it : entities)
		it->reset();
}


void EAFactory::load(const float& screen_w, const float& screen_h)
{
	free();

	this->screen = sf::Vector2f(screen_w, screen_h);
	tools.load(screen_w, screen_h);
	tools.reset();
	
	entities.push_back(new ee::Knight);
	entities.push_back(new ee::Tile);
	entities.push_back(new ee::UnvisibleTile);
	entities.push_back(new ee::Landscape);
	entities.shrink_to_fit();

	amounts.push_back(1);	// Knight
	amounts.push_back(21);	// Tile
	amounts.push_back(21);	// Unvisible Tile
	amounts.push_back(14);	// Landscape
	amounts.shrink_to_fit();
	for (size_t i = 0; i < amounts.size(); ++i)
		entities[i]->load(screen, amounts[i]);
}

bool EAFactory::handle(const sf::Event &event, const sf::Vector2i &addi)
{
	// --- unfold ---
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Right)
		{
			auto activeit = entities.end();
			for (std::vector<ee::Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
				if ((*it)->isActive())
				{
					activeit = it;
					break;
				}

			sf::Vector2i mouse = sf::Vector2i(event.mouseButton.x + -addi.x, -event.mouseButton.y + screen.y + -addi.y);
			for (auto &it : entities)
				if (((activeit != entities.end() && it != (*activeit)) || activeit == entities.end()) && it->unfold(mouse))
				{
					it->setActive(true);
					break;
				}
		}
	}

	for (auto &it : entities)
		if (it->isActive())
		{
			it->handle(event);
			return false;
		}
	// --- unfold ---

	// Type has to be different than VOID and need to be withing range.
	char nwt = tools.getType() == cmm::Kind::VOID ? -1 : (amounts.size() > tools.getType() ? amounts[tools.getType()] : -1);
	tools.handle(event, nwt);

	// Does mouse button or hot key is pressed?
	bool pressed = false;
	sf::Vector2i mouse = cmm::StaticCore::getMousePosition();
	if (tools.isHotKeyPressed())
	{
		if (tools.getType() == cmm::Kind::TILE ||
			tools.getType() == cmm::Kind::UNVISIBLE_TILE ||
			tools.isDeleteMode() ||
			tools.isHotKeyElapsed())
			pressed = true;
	}
	else if (event.type == sf::Event::MouseButtonPressed)
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			mouse = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
			pressed = true;
		}
	
	// Prepare mouse position.
	mouse.x = mouse.x + -addi.x;
	mouse.y = -mouse.y +screen.y + -addi.y;

	// Set Red Backlight
	tools.isRedBack() = false;
	if(tools.getType() != cmm::Kind::VOID && tools.getType() < entities.size())
		if (entities[tools.getType()]->checkCollision(mouse))
			tools.isRedBack() = true;

	// If there is no Red Backlight remove or add.
	if (pressed)
	{
		if (tools.isDeleteMode())
			remove(mouse);
		else if(!tools.isRedBack())
		{
			ee::Item item(-1, tools.getType(), tools.getChosen(), mouse);
			add(item);
		}
	}

	return false;
}

void EAFactory::draw(sf::RenderWindow* &window, const sf::Vector2i &add, const bool &grid)
{
	// Draw entities.
	sf::Vector2i addi = add;
	for (auto &it : entities)
		it->draw(window, addi);

	// Draw current single entity.
	if (tools.getType() != cmm::Kind::VOID && amounts.size() > tools.getType())
	{
		cmm::Sprite* const sprite = entities[tools.getType()]->getSprite(tools.getChosen());
		sprite->setColor(tools.isRedBack() ? cmm::ERROR_COLOR : cmm::LOADING_COLOR);

		// Set valid position.
		if(grid)
			sprite->setPosition(current.x, current.y);
		else
			sprite->setPosition(current.x, current.y - sprite->getHeight());

		window->draw(*sprite);
		sprite->setColor(cmm::LOADING_COLOR);
		tools.thumbnail(window, entities[tools.getType()]->getSprites(), tools.getChosen());
	}

	tools.draw(window);
}

void EAFactory::mechanics(const double &elapsedTime)
{
	if (tools.isUndoKeyElapsed())
	{
		int type;
		sf::Vector2i position;
		if (history.tryUndo(type, position.x, position.y))
			entities[type]->remove(position);
	}

	if (history.isNewLoadVersion())	// clear everything and reload it
	{
		history.clear_local();
		history.fill_local();

		for (auto &it : entities)
			it->reset();

		ee::Item item;
		while (history.next())
		{
			item = history.getItem();
			if (entities[item.type]->add(item))
				entities[item.type]->getItem();
		}
	}

	tools.mechanics(elapsedTime);

	for (auto &it : entities)
		if (it->isActive())
		{
			it->mechanics(elapsedTime);
			break;
		}

	for (auto &it : entities)
		if (it->isModified())
		{
			it->setActive(false); // to be sure
			ee::Item item = it->getItem();
			history.modify(item);
			break;
		}
}

void EAFactory::add(ee::Item &data)
{
	if (data.type == cmm::Kind::VOID)
	{ // should never happen
		//assert(false);
		return;
	}
	
	data.ID = history.getNewID();
	int ID = entities[data.type]->getItem().ID;
	if (entities[data.type]->add(data))
	{
		ee::Item item = entities[data.type]->getItem();
		if (entities[data.type]->isOneAndOnly() && ID != cmm::Kind::VOID)
		{
			ee::Item buf(item); buf.ID = ID;
			history.remove(buf);
		}

		history.add(item);
	}
}

void EAFactory::remove(sf::Vector2i &position)
{
	ee::Item item;
	for (auto rit = entities.rbegin(); rit != entities.rend(); ++rit)
		if ((*rit)->remove(position))
		{
			item = (*rit)->getItem();
			history.remove(item);
			break;
		}
}