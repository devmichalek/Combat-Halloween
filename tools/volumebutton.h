#pragma once
#include "button.h"

class VolumeButton final
{
	cmm::Sound click;
	cmm::Sprite plus;
	cmm::Sprite minus;

	float volume;
	const float min, max;

	bool locked, changed;
	bool plus_pressed;
	bool minus_pressed;

public:
	VolumeButton();
	~VolumeButton();
	void free();

	void load(const float &screen_w, const float &screen_h);
	void setPosition(float left, float right, float bot);
	bool handle(const sf::Event &event);
	void draw(sf::RenderWindow* &window);
	void mechanics(double elapsedTime);

	void fadein(const float &v, const int &max);
	void fadeout(const float &v, const int &min);

	void setGlobalVolume(float volume);
	const float& getGlobalVolume() const;
	void setLocked(bool locked);
	const bool hasChanged();			// Whenever minus button is pressed or plus button is pressed.
	void setChanged(float newVolume);	// It is caused by chat command.
	void setVolume(const float &volume);
};