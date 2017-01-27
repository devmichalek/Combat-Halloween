#pragma once

#include <SFML/Graphics/Color.hpp>
#include <vector>

using namespace std;

class Plant
{
	vector <sf::Uint8> blocks;
public:
	
	bool bg;
	sf::Uint8 nr;
	sf::Uint8 chance;
	int startX, endX;
	int startY, endY;

	Plant();
	~Plant();
	void free();
	
	unsigned getSize();
	void add( sf::Uint8 block );
	bool available( sf::Uint8 block );
};