#pragma once
#include "text.h"
#include "circlebutton.h"
#include <SFML/Graphics/RectangleShape.hpp>

class EADetails final
{
	CircleButton button;
	cmm::Text label;
	cmm::Sprite plank;
	sf::RectangleShape blackLayer;
	cmm::Sprite leftbutton;
	cmm::Sprite rightbutton;

	cmm::Text info;
	cmm::Text titleform;
	cmm::Text titlewritten;
	cmm::Text specsform;
	cmm::Text specswritten;

	int chosen;
	sf::IntRect titlerect;
	sf::IntRect specsrect;

	cmm::Text arrow;
	float arrow_counter;
	float arrow_line;

	bool active;

public:
	EADetails();
	~EADetails();
private:
	void free();
public:
	void reset();

	void load(const float& screen_w, const float& screen_h);
	void handle(const sf::Event &event);
	void drawButton(sf::RenderWindow* &window);
	void draw(sf::RenderWindow* &window);
	void mechanics(const double &elapsedTime);
	bool isActive() { return active; };

private:
	void setText();
	void setTextPosition();
};