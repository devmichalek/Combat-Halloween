#pragma once

#include "templates/chunk.h"
#include <SFML/Graphics/Export.hpp> // sf::Uint8

class Click
{
	
protected:

	// focus on button true/false
	bool focus;	
	
	// click as sound and play as state
	bool play;
	Chunk click;
	
public:
	
	void turn();	// Turn on/off chunk
	void setVolume( sf::Uint8 volume );
};