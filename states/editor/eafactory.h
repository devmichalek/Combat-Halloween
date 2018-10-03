#pragma once
#include "sprite.h"

#include "eetile.h"
#include "eeknight.h"
#include "eelandscape.h"

#include "eakind.h"
#include "eahistory.h"
#include "eatools.h"

class EAFactory	: public EAKind
{
	int width;
	float screen_w;
	float screen_h;

	bool change, redBacklight;
	std::vector<int> amounts;
	std::vector<std::vector<cmm::Sprite*>> factory;

	EATools tools;
	EAHistory history;

	// Entities
	ee::Knight eKnight;
	ee::Tile eTiles;
	ee::Tile eUnTiles;	// Unvisible Tiles
	ee::Landscape eLandscape;

public:
	EAFactory();
	~EAFactory();
private:
	void free();
public:
	void reset();

	void load(const float& screen_w, const float& screen_h);
	bool handle(const sf::Event &event, const int &addX, const int &addY);
	void draw(sf::RenderWindow* &window, const int &addX, const int &addY);
	void mechanics(const double &elapsedTime);

	void setPosition(float x, float y);
	bool isChange();
	bool isDeleteMode();

	const int& getType() const;
	const int& getChosen() const;

private:
	void drawPrivate(sf::RenderWindow* &window, const int &addX, const int &addY);	// draw
	bool checkCollision(const int& x, const int& y);
	void add(int& x, int& y, int t, int c, int id = -1, std::string ai = "", bool con = false);
	void remove(int& x, int& y);
	void unfold(int& x, int& y);	// show options (if they are)

	bool handle_deck(const sf::Event &event);
	void mechanics_deck(const double &elapsedTime);
};