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

	Sound_button( bool play = true );
    ~Sound_button();
	void free();

	void load( string path, int bot, int screen_w );
	void setExplanator( string text, int screen_w );
    void draw( sf::RenderWindow* &window );
    void handle( sf::Event &event );
	
	void setState( sf::Uint8 s );
	int getBot();
	bool isChanged();

	void fadein( int i = 1, int max = 255 );
	void fadeout( int i = 1, int min = 0 );
};