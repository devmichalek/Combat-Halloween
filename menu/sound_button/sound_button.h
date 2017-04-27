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
	
	float y_state;
	float scale;
	
public:
	
	// Basics.
	Sound_button( bool play = true );
    ~Sound_button();
	void free();

	void load( string path, float y, unsigned w );
	void handle( sf::Event &event, int r_x, int r_y );
	void draw( sf::RenderWindow* &window );
	
	void fadein( int i = 1, int max = 0xFF );
	void fadeout( int i = 1, int min = 0 );
	
	// In addition.
	void setState( sf::Uint8 s );
	int getBot();
	bool isChanged();
	void setExplanator( string text );
	float getYScale();
	
	// Window.
	void setScale( float s_x, float s_y );
	void setView( unsigned w, int r_x, int r_y );
};