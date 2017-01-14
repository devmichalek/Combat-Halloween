/**
    click.h
    Purpose: class Click - to play click.wav with state called focus for buttons.

    @author Adrian Michalek
    @version 2016.10.14
	@email adrmic98@gmail.com
*/

#pragma once

#include "sound/chunk.h"
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
	
	void turn();	// Turn on/off chunk
	bool isPlayable();
	void setVolume( sf::Uint8 volume );
};