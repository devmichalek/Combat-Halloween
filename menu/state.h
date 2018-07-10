#pragma once
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Clock.hpp>
class State
{
protected:
	bool prev;
	bool next;
	bool exit;
	virtual bool isReady() const = 0;
public:
	State();
	~State();
	void free();
	bool isPrev() const;
	bool isNext() const;
	bool isExit() const;
	bool isState() const;
};

class Username
{
public:
	static char* username;
	static char* getUsername() { return username; }
	static sf::Color getErrorColor() { return sf::Color(0xF2, 0x58, 0x3E); }
	static sf::Color getSuccessColor() { return sf::Color(0xFF, 0xDE, 0x00); }
	static sf::Color getGreenColor() { return sf::Color(0x58, 0x70, 0x58); }
	static sf::Color getLockedColor() { return sf::Color(0xDD, 0xDD, 0xDD); }
	static sf::Color getLoadingColor() { return sf::Color::White; }
};

// Usage: If timePassed() - checks whether amount of set time elapsed (do update every n sec), then getFPS()
class FPS
{
	static sf::Clock clock;
	static float currentTime;
	static unsigned fps;

	static double counter;
	static double max;
public:
	static void mechanics(double elapsedTime);
	static bool timePassed();
	static const unsigned& getFPS();
};