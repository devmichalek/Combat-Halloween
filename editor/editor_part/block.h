#pragma once

#include <SFML/Graphics/Color.hpp>

struct Block
{
	sf::Uint8 w;
	sf::Uint8 n;
	float x;
	float y;
	
	Block( sf::Uint8 w = 0, sf::Uint8 n = 0, float x = 0, float y = 0 );
	~Block();
};