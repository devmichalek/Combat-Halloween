#pragma once
#include "sprite.h"
#include "eaentityspecial.h"
#include "eaentitygrid.h"
#include "eaentityrect.h"
#include "eakind.h"
#include "eahistory.h"
#include "eatools.h"

// This objects only draws things and collect them.
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
	EAEntitySpecial entityKnight;
	EAEntityGrid entityTiles;
	EAEntityGrid entityUnTiles;	// Unvisible Tiles
	EAEntityRect entityLandscape;

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


	void setPosition(float x, float y);
	bool isChange();
	bool isDeleteMode();

	// For File Manager
	const std::vector<std::string>& getHistory();
	void setHistory(std::vector<std::string> newHistory);

	const int& getType() const;
	const int& getChosen() const;

private:
	void drawPrivate(sf::RenderWindow* &window, const int &addX, const int &addY);	// draw
	bool isCellEmpty(const int& x, const int& y);
	void add(const int& x, const int& y);
	void remove(const int& x, const int& y);
	//void unfold(const int& x, const int& y);	// show options (if they are)
};