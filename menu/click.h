/**
    click.h
    Purpose: class Click - to play click.wav with state called focus for buttons.

    @author Adrian Michalek
    @version 2016.10.14
	@email adrmic98@gmail.com
*/

#pragma once

#include "sound/chunk.h"
#include <string>
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

	Click();
	~Click();
	void free();
	
	void turn();
	void turnOn();
	void turnOff();
	
	bool isPlayable();
	void setVolume( sf::Uint8 volume );
	
	void setChunkName( std::string text );
	void loadChunk( std::string text );
	void playChunk();
};