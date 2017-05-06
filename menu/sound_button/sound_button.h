/**
    sound_button.h
    Purpose: class Sound_button - for music and chunk button for changing state (on/off) - switch.

    @author Adrian Michalek
    @version 2016.10.13
	@email adrmic98@gmail.com
*/

#pragma once

#include "drawable/sprite.h"
#include "menu/click.h"
#include "menu/explanator/explanator.h"

// Class for chunk/music button
class Sound_button :public Click
{
	Explanator explanator;
	MySprite button;
	MySprite scratch;
	
	// music/chunk is on/off
	sf::Uint8 state;
	
public:
	
	// Basics.
	Sound_button( bool play = true );
    ~Sound_button();
	void free();

	void load( string path, float y = 10 );
	void handle( sf::Event &event );
	void draw( sf::RenderWindow* &window );
	
	void fadein( int i = 1, int max = 0xFF );
	void fadeout( int i = 1, int min = 0 );
	
	// In addition.
	void setState( sf::Uint8 s );
	float getBot();
	bool isChanged();
	void setExplanator( string text );
};