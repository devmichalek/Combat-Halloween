/**
    title.h
    Purpose: class Title - to show sprite (title).

    @author Adrian Michalek
    @version 2016.10.13
	@email adrmic98@gmail.com
*/

#pragma once

#include "drawable/sprite.h"
#include "drawable/text.h"

class Title
{
	MySprite background;
	MySprite belt;
	// MyText title;
	// MyText title_sec;
	// MyText version;
	
public:
	
	// Basics.
	Title();
    ~Title();
	void free();
	
	void load( unsigned screen_w, unsigned screen_h );
	void draw( sf::RenderWindow &window );
	
	void fadein( int i = 1, int max = 255 );
	void fadeout( int i = 1, int min = 0 );
	
	// In addtion.
	const int getBot()const;	// accessor
	sf::Uint8 getAlpha();
};