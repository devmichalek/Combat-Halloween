#pragma once
#include "text.h"
#include "sound.h"
#include "sprite.h"
#include "request.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class MenuInformation
{
	float screen_w;
	float screen_h;
	std::string username_str;

	cmm::Text money;
	cmm::Text money_form;
	cmm::Text username;
	cmm::Text username_form;

	cmm::Sprite plank;
	cmm::Sprite scene;
	cmm::Sprite background;
	cmm::Thread thread;

public:
	MenuInformation();
	~MenuInformation();
	void free();

	void load(float screen_w, float screen_h);
	void draw(sf::RenderWindow* &window);
	void mechanics();
	void fadein(float v = 1, int max = 0xFF);
	void fadeout(float v = 1, int min = 0);

	void setThread();
	void setMoney();
	void reloadMoney();
	bool isReady() const;		// money is loaded correctly from database
	int getBackgroundAlpha() const;

private:
	sf::Color getErrorColor() { return sf::Color(0xF2, 0x58, 0x3E); }
	sf::Color getSuccessColor() { return sf::Color(0xFF, 0xDE, 0x00); }
};