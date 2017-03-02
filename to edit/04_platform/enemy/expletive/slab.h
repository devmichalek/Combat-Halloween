#pragma once

#include "sound/chunk.h"
#include <string>
#include <SFML/Graphics/Export.hpp> // sf::Uint8

class Slab
{
	
protected:

	// click as sound and play as state
	bool flag;
	Chunk click;
	
public:

	Slab();
	~Slab();
	void free();
	
	void turn();
	void turnOn();
	void turnOff();
	
	bool isPlayable();
	void setVolume( sf::Uint8 volume );
	
	void setName( std::string text );
	void load( std::string text );
	void play();
};