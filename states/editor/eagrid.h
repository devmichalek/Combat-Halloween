#pragma once
#include "text.h"
#include "circlebutton.h"
#include "eventwindow.h"
#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>

// This object draw lines, display text and arrows
class EAGrid	// Editor Action Grid
{
	enum ARROWS
	{
		LEFT = 0,
		RIGHT,
		TOP,
		BOT,
		CENTER,
		COUNT
	};

	std::vector<CircleButton*> arrows;

	bool grid, change;		// is grid ON/OFF, is view moved YES/NO
	int width;				// tile width
	int offsetX, offsetY;	// values for addX and addY
	int addX, addY;			// additional x and y (window view x y)
	int gridX, gridY;		// calculated x y grid
	int mouseX, mouseY;		// current mouse x and y
	int limitX, limitY;		// max x and y that can be reached
	float screen_w, screen_h;

	sf::RectangleShape lineX;
	sf::RectangleShape lineY;
	sf::RectangleShape suppX;
	sf::RectangleShape suppY;
	cmm::Text xyText;

public:
	EAGrid();
	~EAGrid();
private:
	void free();
public:
	void reset();

	void load(const float &screen_w, const float &screen_h, const int &width);
	bool handle(const sf::Event& event);
	void draw(sf::RenderWindow* &window);
	void mechanics(bool deleteMode);

	const int& getLimitX() const;
	const int& getLimitY() const;
	const int& getAddX() const;
	const int& getAddY() const;
	
	// Get grid/mouse x,y
	int getX() const;
	int getY() const;

	void turnOn();
	void turnOff();
	const bool& isActive() const;
	// const bool& isChange() const;

private:
	void setText();
	void checkArrows();
	void setArrows();

	bool isAbleToGoLeft();
	bool isAbleToGoRight();
	bool isAbleToGoUp();
	bool isAbleToGoDown();
	bool isAbleToCenter();
};