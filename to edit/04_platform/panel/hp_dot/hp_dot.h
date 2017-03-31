#pragma once

#include "SFML/Graphics.hpp"

class Hp_dot
{
public:
	
	bool active;
	float x, y;
	float radius;
	sf::Uint8 alpha;
	
	Hp_dot();
	~Hp_dot();
};