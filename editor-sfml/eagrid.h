#pragma once
#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "text.h"
class EAGrid	// Editor Action Grid
{
	bool grid;
	int width;
	float mouseX, mouseY;
	float screen_w, screen_h;
	float gridX, gridY;
	sf::RectangleShape lineX;
	sf::RectangleShape lineY;
	sf::RectangleShape suppX;
	sf::RectangleShape suppY;
	cmm::Text xyText;

	enum TEXTS
	{
		GRIDFORM = 0,
		GRID,
		CHOSENFORM,
		CHOSEN,
		CATEGORYFORM,
		CATEGORY,
		SIZE
	};

	std::vector<cmm::Text*> texts;

public:
	EAGrid();
	~EAGrid();
private:
	void free();
public:
	void reset();

	void load(const float &screen_w, const float &screen_h, const int &width);
	void handle(const sf::Event& event);
	void draw(sf::RenderWindow* &window);

	float getX() const;
	float getY() const;
	void turnOn();
	void turnOff();
	const bool& isActive() const;
	void setGridStr();
	void setChosenStr(std::string line);
	void setCategoryStr(std::string line);
};