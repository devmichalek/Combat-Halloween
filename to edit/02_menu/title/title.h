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
	MySprite belt;
	MyText title;
	
public:
	
	Title();
    ~Title();
	void free();

    void load( const int& screen_w );
    void draw( sf::RenderWindow &window );
	
	const int getBot()const;	// accessor
	
	void fadein( int i = 1, int max = 255 );
	void fadeout( int i = 1, int min = 0 );
};