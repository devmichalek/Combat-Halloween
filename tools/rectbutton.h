#pragma once
#include "text.h"
#include "eventwindow.h"
#include <SFML/Graphics/Rectangleshape.hpp>
#include <vector>


class Rectbutton
{
	float alpha;
	float alphaBorders;

	bool focus;
	bool clicked;
	sf::Uint8 state;

	cmm::Text text_one;
	cmm::Text text_two;
	std::vector <sf::RectangleShape> rects;

public:
	Rectbutton();
	~Rectbutton();
	void free();

	void setFont(const char* path);
	void create(std::string line, int size, float ply);
	void handle(const sf::Event &event);
	void draw(sf::RenderWindow* &window);
	void mechanics(const double &elapsedTime);

	// Fades.
	void fadein			(const float &v, const int &max);
	void fadeinBorders	(const float &v, const int &max);
	void fadeinGlobal	(const float &v, const int &max);
	void fadeout		(const float &v, const int &min);
	void fadeoutBorders	(const float &v, const int &min);
	void fadeoutGlobal	(const float &v, const int &min);

	// Setters.
	void move(float x, float y);
	void setPosition(float x, float y);
	void center(float x, float y, int w, int h);
	void setColor(sf::Color color);
	void setColorText(sf::Color color);
	void setAlpha(float alpha = 0);
	void setAlphaBorders(float alpha = 0);

	// Getters.
	float getAlpha();
	float getAlphaBorders();
	sf::Uint8& getState();
	bool& getFocus();
	bool& getClicked();

	// Other accessors.
	const float& getX() const;
	const float& getY() const;
	const float& getWidth() const;
	float getHeight() const;

	const float& getLeft() const;
	float getRight() const;
	const float& getTop() const;
	float getBot() const;

	// Collision detection.
	bool checkCollision(float x, float y, float w = 0, float h = 0) const;
};