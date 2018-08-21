#pragma once
#include "sprite.h"

// This objects only draws things and give feedback about type/chosen/grid stuff.
class EAFactory
{
	enum KIND
	{
		VOID = -1,
		KNIGHT,
		TILE,
		UNVISIBLE_TILE,
		LANDSCAPE,
		FOE,
		LIGHTPOINT,
		AMOUNT
	};

	int type;
	int chosen;
	bool change;
	std::vector<int> amounts;
	std::vector<std::vector<cmm::Sprite*>> factory;

public:
	EAFactory();
	~EAFactory();
private:
	void free();
public:
	void reset();

	void load(const float& screen_w, const float& screen_h);
	bool handle(const sf::Event &event);
	void draw(sf::RenderWindow* &window);

	// Grid
	void setPosition(float x, float y);
	bool isGridChange();		// type has changed?
	bool isGridNeeded();
	std::string getTypeStr();
	std::string getChosenStr();
};