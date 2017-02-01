/**
    loading.h
    Purpose: class Loading - to show progress during loading objects.

    @author Adrian Michalek
    @version 2016.10.05
	@email adrmic98@gmail.com
*/

#pragma once

#include "drawable/text.h"
#include "drawable/sprite.h"

class Loading
{
	MyText text;			// text "loading"
	MySprite bg;			// background
	sf::Uint8 state;		// show percents
	
	sf::Uint8 counter;		// to set offsets
	sf::Uint8 max;			// how many offset's
	MySprite progress_bar;	// animation
	
public:
	
	Loading();
	~Loading();
	void free();
	
	void load( unsigned screen_w, unsigned screen_h );	// load textures
	void draw( sf::RenderWindow* &window );				// render textures
	
	const sf::Uint8& getState() const; 					// getter
};