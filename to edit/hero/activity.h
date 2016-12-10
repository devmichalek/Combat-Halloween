#pragma once

#include "templates/sprite.h"

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
	bool Do();
	
	void setActive( bool a );
	bool isActive();
	
	void setLine( sf::Uint8 nr );
	sf::Uint8 getLine();
};