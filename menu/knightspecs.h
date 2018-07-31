#pragma once
#include "text.h"
#include "sound.h"
#include "sprite.h"
#include "request.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

class Knightspecs
{
	float screen_w;
	float screen_h;

	enum FEATURES
	{
		HEART_POINTS = 0,
		ARMOUR,
		MOVEMENT_SPEED,
		DAMAGE,
		ATTACK_SPEED,
		LUCKINESS,
		EXPERIENCE,
		LEVEL,
		AMOUNT
	};

	cmm::Sprite plank;
	cmm::Sprite topgear, botgear;

	// Animation.
	float offset;
	float max_offset;
	cmm::Sprite knight;

	cmm::Sound click;
	cmm::Thread thread;

	// View, specs
	cmm::Text categories;
	std::vector <cmm::Text*> values;

public:
	Knightspecs();
	~Knightspecs();
	void free();

	void load(float screen_w, float screen_h);
	void draw(sf::RenderWindow* &window);
	void mechanics(double elapsedTime);
	void fadein(float v = 1, int max = 0xFF);
	void fadeout(float v = 1, int min = 0);

	void setThread();
	void reloadThread();
	bool isReady() const;	// values are loaded correctly from database
	void setVolume(float volume);
private:
	void setValues();
	void position();
};