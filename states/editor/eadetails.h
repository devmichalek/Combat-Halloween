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
	std::string titlestr;
	std::string specsstr;
	std::string titleresetstr;
	std::string specsresetstr;

	int chosen;
	sf::IntRect titlerect;
	sf::IntRect specsrect;

	unsigned max_length_title;
	unsigned min_length_title;
	unsigned max_length_specs;
	unsigned min_length_specs;

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
	void setTitle(std::string newTitle);
	void setDescription(std::string newDescription);

private:
	void setText();
	void setTextPosition(float specswidth = -1);
	bool isPossibleKey(const sf::Uint8 &code) const;
};