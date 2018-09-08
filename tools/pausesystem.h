#pragma once
#include "sound.h"
#include "sprite.h"
#include "text.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class PauseSystem
{
	cmm::Text text;
	cmm::Sound click;
	cmm::Sprite blackout;

	bool active;
	bool key_released;

public:
	PauseSystem();
	~PauseSystem();
	void free();

	void load(const float &screen_w, const float &screen_h);
	void handle(const sf::Event &event);
	void draw(sf::RenderWindow* &window);
	void fadein(const float &v, const int &max);
	void fadeout(const float &v, const int &min);

	const bool& isActive() const;
	void turnOnOff();
	float getAlpha() const;
	void setVolume(const float &volume);
};