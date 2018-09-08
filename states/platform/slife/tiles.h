#pragma once
#include "sprite.h"
//#include "request.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
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

	std::vector <cmm::Sprite*> sprites;
	std::vector <std::vector <sf::Int8>> tiles;
	std::vector <std::vector <float>> alphas;

	// Thread stuff.
	/*string error;
	MyThread thread;*/

public:
	Tiles();
	~Tiles();
	void free();
	void reset();
	void load(float screen_w, float screen_h);
	void draw(sf::RenderWindow* &window, sf::Shader &shader);

	/*bool isNull();
	bool isReady();
	void setThread(string message);
	void prepare(string message);
	string getError();*/

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