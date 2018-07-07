#pragma once
#include "sprite.h"
#include "sound.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

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
	void setVolume(float volume);
	
	void draw(sf::RenderWindow* &window);
	void fadein(float v = 1, int max = 0xFF);
	void fadeout(float v = 1, int min = 0);

	float getLeft() const;
	float getRight() const;
	float getTop() const;
	float getBot() const;
	float getWidth() const;
	float getHeight() const;

	void lock();
	void unlock();
	void reset();
};

class SquareButton :public Button
{
	bool pressed;

public:
	SquareButton();
	~SquareButton();
	void free();

	void handle(sf::Event& event);
	void setPressed();
	const bool& isPressed() const;
};

class Circlebutton :public Button
{
	bool active;
	bool changed;

public:
	Circlebutton();
	~Circlebutton();
	void free();

	bool handle(sf::Event& event);
	bool isActive();
	void setActive(bool active);
	void changeActive();
	bool hasChanged();
	void setChanged(bool changed);
};

class LinkButton :public Button
{
	std::string url;

public:
	LinkButton();
	~LinkButton();
	void free();

	void handle(sf::Event& event);
	void setUrl(std::string newUrl);
	void openWebsite();
};

class VolumeButton
{
	cmm::Sound click;
	cmm::Sprite plus;
	cmm::Sprite minus;

	float volume;
	const float min, max;

	bool locked;
	bool plus_pressed;
	bool minus_pressed;

public:
	VolumeButton();
	~VolumeButton();
	void free();

	void load(float screen_w, float screen_h);
	void setPosition(float left, float right, float bot);
	bool handle(sf::Event& event);
	void draw(sf::RenderWindow* &window);
	void mechanics(double elapsedTime);

	void fadein(float v = 1, int max = 0xFF);
	void fadeout(float v = 1, int min = 0);

	void setGlobalVolume(float volume);
	const float& getGlobalVolume() const;
	void setLocked(bool locked);
	bool hasChanged() const; // Whenever minus button is pressed or plus button is pressed.
	void setVolume(float volume);
};