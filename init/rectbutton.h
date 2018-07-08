#pragma once
#include "text.h"
#include <SFML/Graphics/Rectangleshape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
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
	void handle(sf::Event& event);
	void draw(sf::RenderWindow* &window);
	void mechanics(double elapsedTime);

	// Fades.
	void fadein(float v = 1, int max = 0xFF);
	void fadeinBorders(float v = 1, int max = 0xFF);
	void fadeinGlobal(float v = 1, int max = 0xFF);
	void fadeout(float v = 1, int min = 0);
	void fadeoutBorders(float v = 1, int min = 0);
	void fadeoutGlobal(float v = 1, int min = 0xFF);

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