#pragma once
#include "sprite.h"
#include "sound.h"
#include "eventwindow.h"

class Button
{
protected:
	cmm::Sound click;
	cmm::Sprite button;
	bool locked;

public:
	Button();
	virtual ~Button();
	virtual void free() = 0;

	void load(const char* path, bool locked = false, int numOfOffsets = 3);
	void setPosition(float x, float y);
	void setScale(float x, float y);
	void setVolume(const float &volume);
	
	void draw(sf::RenderWindow* &window);
	void fadein(const float &v, const int &max);
	void fadeout(const float &v, const int &min);

	const float& getLeft() const;
	float getRight() const;
	const float& getTop() const;
	float getBot() const;
	float getWidth() const;
	float getHeight() const;

	void lock();
	void unlock();
	void reset();
};
