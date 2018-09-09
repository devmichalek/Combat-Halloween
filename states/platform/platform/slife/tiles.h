#pragma once
#include "sprite.h"
//#include "request.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include <unordered_map>

class TileP2D	// Tile Point 2D
{
public:
	int x, y;
	TileP2D(int x, int y) : x(x), y(y) {};
};

struct TileHashFunc	// Tile Hash Function
{
	size_t operator()(const TileP2D &p) const
	{
		size_t h1 = std::hash<int>()(p.x);
		size_t h2 = std::hash<int>()(p.y);
		return h1 ^ (h2 << 1);
	}
};

struct TileEquilFunc	// Tile Equil Function
{
	bool operator()(const TileP2D &l, const TileP2D &r) const
	{
		return (l.x == r.x) && (l.y == r.y);
	}
};

using Tile2DMap = std::unordered_map<TileP2D, float, TileHashFunc, TileEquilFunc>;	// holds alpha

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

	std::vector <cmm::Sprite*> sprites;
	char** pos;
	Tile2DMap* alphas;

public:
	Tiles();
	~Tiles();
private:
	void free();
public:
	void reset();
	void load(const float &screen_w, const float &screen_h);
	void draw(sf::RenderWindow* &window/*, sf::Shader &shader*/);

	void setBorderX(float& x);
	void setBorderY(float& y);
	const float& getBorderX() const;
	const float& getBorderY() const;
	const float& getScreenWidth() const;
	const float& getScreenHeight() const;

	void switchCollision(bool collision = true);
	bool checkCollisionRect(sf::Rect <float>& rect);
	void tickGravity(sf::Rect <float>& rect, double elapsedTime);
};