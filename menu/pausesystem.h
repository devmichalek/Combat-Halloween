#pragma once
#include "sound.h"
#include "sprite.h"
#include "text.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class Pausesystem
{
	cmm::Text text;
	cmm::Sound click;
	cmm::Sprite blackout;

	bool active;
	bool key_released;

public:
	Pausesystem();
	~Pausesystem();
	void free();

	void load(float screen_w, float screen_h);
	void handle(sf::Event& event);
	void draw(sf::RenderWindow* &window);

	void fadein(float v = 1, int max = 0xFF);
	void fadeout(float v = 1, int min = 0);

	const bool& isActive() const;
	void turnOnOff();
	int getAlpha() const;
	void setVolume(float volume);
};