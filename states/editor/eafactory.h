#pragma once
#include "eatools.h"
#include "eahistory.h"

#include "eetile.h"
#include "eeknight.h"
#include "eelandscape.h"

class EAFactory final
{
	EATools tools;
	EAHistory history;

	sf::Vector2f screen;
	sf::Vector2f current;
	std::vector<int> amounts; // Number of types of entity.
	std::vector<ee::Entity*> entities;

public:
	EAFactory();
	~EAFactory();
	void free();
	void reset();

	void load(const float& screen_w, const float& screen_h);
	bool handle(const sf::Event &event, const sf::Vector2i &add);
	void draw(sf::RenderWindow* &window, const sf::Vector2i &add, const bool &grid);
	void print(sf::RenderWindow* &window);
	void mechanics(const double &elapsedTime);

	bool isActive()						{ return tools.details.isActive(); }
	bool isChange()						{ return tools.isChange(); }
	bool isDeleteMode()					{ return tools.isDeleteMode(); }
	const int& getType() const			{ return tools.getType(); }
	const int& getChosen() const		{ return tools.getChosen(); }
	void setPosition(float x, float y)	{ current = tools.getType() != cmm::Kind::VOID ? sf::Vector2f(x, y) : sf::Vector2f(0, 0); }

private:
	void add(ee::Item &data);
	void remove(sf::Vector2i &position);
};