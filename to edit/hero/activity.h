#pragma once

#include "templates/sprite.h"

class Activity
{
	
public:
	sf::Uint8 line;
	sf::Uint8 counter;
	bool active;
	
	Activity();
	~Activity();
	void free();
	void summarize();
};