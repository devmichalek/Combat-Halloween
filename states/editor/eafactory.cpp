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
	screen = sf::Vector2f(0.0f, 0.0f);
	current = sf::Vector2f(0.0f, 0.0f);

	tools.reset();
	history.reset();

	for (auto &it : entities)
		it->reset();
}


void EAFactory::load(const float& screen_w, const float& screen_h)
{
	free();

	this->screen = sf::Vector2f(screen_w, screen_h);
	history.reset();
	tools.load(screen_w, screen_h);
	tools.reset();
	
	entities.push_back(new ee::Knight);
	//entities.push_back(new ee::Tile);
	//entities.push_back(new ee::Landscape);

	amounts.push_back(1);	// Knight
	//amounts.push_back(21);	// Tile
	//amounts.push_back(14);	// Landscape
	for (size_t i = 0; i < amounts.size(); ++i)
		entities[i]->load(screen, amounts[i]);
}

bool EAFactory::handle(const sf::Event &event, const sf::Vector2i &addi)
{
	// Type has to be different than VOID and need to be withing range.
	char t = tools.getType() == cmm::Kind::VOID ? -1 : (amounts.size() > tools.getType() ? amounts[tools.getType()] : -1);
	if (tools.handle(event, t))
		return false;

	// --- unfold ---
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Right)
		{
			sf::Vector2i mouse = sf::Vector2i(event.mouseButton.x + (addi.x * -1), event.mouseButton.y * -1 + screen.y + (addi.y * -1));

			for (auto &it : entities)
				if (it->unfold(mouse))
					break;
		}
	}

	for (auto &it : entities)
		if (it->isActive())
			return false;
	// --- unfold ---

	// Does mouse button or hot key is pressed?
	bool pressed = false;
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
			pressed = true;

	sf::Vector2i mouse = cmm::StaticCore::getMousePosition();
	int mouseX = mouse.x + (addi.x * -1);
	int mouseY = mouse.y * -1 + screen.y + (addi.y * -1);

	// Set Red Backlight
	tools.isRedBack() = false;
	for (auto &it : entities)
		if (it->checkCollision(sf::Vector2i(mouseX, mouseX)))
		{
			tools.isRedBack() = true;
			break;
		}

	// If there is no Red Backlight remove or add.
	if (pressed && !tools.isRedBack())
		tools.isDeleteMode() ? remove(mouse) : add(mouse, tools.getType(), tools.getChosen());

	// History handle.
	history.handle(event);

	return false;
}

void EAFactory::draw(sf::RenderWindow* &window, const sf::Vector2i &add)
{
	// Draw entities.
	sf::Vector2i addi = add;
	for (auto &it : entities)
		it->draw(window, addi);

	// Draw current single entity.
	if (tools.getType() != cmm::Kind::VOID)
	{
		cmm::Sprite* const sprite = entities[tools.getType()]->getSprite(tools.getChosen());
		sprite->setColor(tools.isRedBack() ? cmm::ERROR_COLOR : cmm::LOADING_COLOR);
		sprite->setPosition(current.x, current.y);
		window->draw(*sprite);
		sprite->setColor(cmm::LOADING_COLOR);
		tools.thumbnail(window, entities[tools.getType()]->getSprites(), tools.getChosen());
	}

	tools.draw(window);
}

void EAFactory::mechanics(const double &elapsedTime)
{
	int t;
	sf::Vector2i position;
	if (history.undo(t, position.x, position.y))
		entities[t]->remove(position);

	if (history.isNewLoadVersion())	// clear everything and reload it
	{
		history.clear_local();
		history.fill_local();

		for (auto &it : entities)
			it->reset();

		while (history.next())
		{
			char t, c; history.getTC(t, c);
			history.getXY(position.x, position.y);
			int id; history.getID(id);
			std::string ai; history.getAI(ai);

			if (id == ee::Item::VOID)
				id = history.getNewID();

			if (entities[t]->add(position, id, c, ai))
				ee::Item item = entities[t]->getItem();
		}
	}

	tools.mechanics(elapsedTime);

	for (auto &it : entities)
		it->mechanics(elapsedTime);
}

void EAFactory::remove(sf::Vector2i &position)
{
	for (size_t i = entities.size() - 1; i >= 0; --i)
		if (entities[i]->remove(position))
			break;
}

void EAFactory::add(sf::Vector2i &position, int type, int chosen)
{
	if (type == cmm::Kind::VOID)
		return; // should never happen

	int ID = history.getNewID();

	if (entities[type]->add(position, ID, chosen))
	{
		ee::Item item = entities[type]->getItem();
		history.add(type, chosen, position.x, position.y, item.ai, ID);
	}
}