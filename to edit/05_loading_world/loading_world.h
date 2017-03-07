/**
    loading_world.h
    Purpose: class Loading_world shows gears working.

    @author Adrian Michalek
    @version 2017.02.02
	@email adrmic98@gmail.com
*/

#pragma once

#include "drawable/text.h"
#include "drawable/sprite.h"

class Loading_world
{
	MyText text;	// text
	MySprite bg;	// background
	
	int state;
	bool ready;
	sf::Uint8 counter;		// to set offsets
	sf::Uint8 max;			// how many offset's
	MySprite progress_bar;	// animation
	
public:
	
	Loading_world();
	~Loading_world();
	void free();
	void reset();
	
	void load( unsigned screen_w, unsigned screen_h );	// load textures
	void draw( sf::RenderWindow* &window );				// render textures
	
	void fadein( int j = 1, int max = 0xFF );
	void fadeout( int j = 1, int min = 0 );
	
	void setReady();
	void setText( string line );
	bool nextState(); 	// getter
	
	int getState();
	void setState( int s );
	bool readyToLoad();
};