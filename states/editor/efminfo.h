#pragma once
#include "sprite.h"
#include "text.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class EFMInfo
{
	cmm::Sprite plank;
	sf::RectangleShape blackLayer;

	cmm::Text openedText;
	cmm::Text openedFormText;
	cmm::Text chosenText;
	cmm::Text chosenFormText;
	cmm::Text msgText;

public:
	EFMInfo();
	~EFMInfo();
private:
	void free();
public:
	void reset();

	void load(const float &screen_w, const float &screen_h);
	void drawPlank(sf::RenderWindow* &window);
	void draw(sf::RenderWindow* &window);
	void drawLayer(sf::RenderWindow* &window);
	void mechanics(const double &elapsedTime);

	bool isMsgTextActive();
	void setMsgTextActive(bool active = true);
	void setOpenedText(std::string msg = "-");
	std::string setChosenText(std::string msg = "-");
	void setMsgText(std::string msg);

	float getLeft();
	float getRight();
	float getTop();
	float getBot();
	sf::FloatRect getRect();
};