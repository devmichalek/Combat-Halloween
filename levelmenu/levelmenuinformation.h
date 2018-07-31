#pragma once
#include "text.h"
#include "sound.h"
#include "sprite.h"
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class LevelMenuInformation
{
	float screen_w;
	float screen_h;

	enum Types
	{
		MAIN = 0,
		MINE,
		BYUSERS,
		SIZE
	};

	cmm::Sprite plank;
	cmm::Sprite background;
	cmm::Sprite plankbar;
	int chosen;
	std::vector<cmm::Text*> texts;
	cmm::Sound sound;

public:
	LevelMenuInformation();
	~LevelMenuInformation();
	void free();

	void load(float screen_w, float screen_h);
	void draw(sf::RenderWindow* &window);
	void handle(sf::Event &event);
	void fadein(float v = 1, int max = 0xFF);
	void fadeout(float v = 1, int min = 0);

private: void prepareChosen(); public:
	
	void setVolume(float newVolume);
	int getBackgroundAlpha() const;
	const int& getChosen() const;
};