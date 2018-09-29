#pragma once
#include "sprite.h"
#include "eventwindow.h"
#include <vector>

class Tiles
{
	int width;
	float screen_w;
	float screen_h;
	float border_x;
	float border_y;

	// --- Test.
	bool collision;
	sf::RectangleShape rect;
	// ---

	int max;
	char** tiles;
	char** untiles;	// unvisible tiles
	sf::Rect<int> singleTile;
	std::vector <cmm::Sprite*> sprites;

public:
	Tiles();
	~Tiles();
private:
	void free();
public:
	void reset();
	void load(const float &screen_w, const float &screen_h);
	void draw(sf::RenderWindow* &window/*, sf::Shader &shader*/);
	void read(std::vector<std::string> &vec);

	void setBorderX(float& x);
	void setBorderY(float& y);
	const float& getBorderX() const;
	const float& getBorderY() const;
	const float& getScreenWidth() const;
	const float& getScreenHeight() const;

	void switchCollision(bool collision = true);
	bool checkCollisionV(sf::Rect<int> &rect, const char add = 0); // vertical
	bool checkCollisionH(sf::Rect<int> &rect, const char add = 0); // horizontal
};