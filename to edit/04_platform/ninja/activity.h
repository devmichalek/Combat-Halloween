/**
    activity.h
    Purpose: class Activity contains counter, line for counter, and check if its active.

    @author Adrian Michalek
    @version 2017.12.12
	@email adrmic98@gmail.com
*/

#pragma once

#include "drawable/sprite.h"

class Activity
{
	
protected:
	bool active;
	sf::Uint8 line;
	sf::Uint8 counter;
	
public:
	Activity();
	~Activity();
	void free();
	
	void start();
	void check();
	bool run();
	
	void setActive( bool a );
	bool isActive();
	
	void setLine( sf::Uint8 nr );
	sf::Uint8 getLine();
	sf::Uint8 getCounter();
};