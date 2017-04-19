#pragma once

#include "SFML/Graphics.hpp"

class Hp_dot
{
public:
	
	bool active;
	float x, y;
	float scale;
	double angle;
	
	Hp_dot();
	~Hp_dot();
};