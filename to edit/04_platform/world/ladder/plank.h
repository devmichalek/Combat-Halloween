#pragma once

#include "04_platform/world/brick/block.h"
#include <SFML/Graphics/Color.hpp>

class Plank :public Block
{
	
public:
	
	sf::Uint8 red;
	sf::Uint8 green;
	sf::Uint8 blue;
	
	Plank();
	~Plank();
	void free();
};