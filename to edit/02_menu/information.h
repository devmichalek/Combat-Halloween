/**
    information.h
    Purpose: class Information - to show text during keyboard state.

    @author Adrian Michalek
    @version 2016.11.02
	@email adrmic98@gmail.com
*/

#pragma once

#include "drawable/text.h"
#include "drawable/sprite.h"

class Information
{
	int nr;
	MyText* text;
	
	int info_nr;
	MyText* info_text;
	
public:

	Information();
    ~Information();

    void load( int right, int top, int screen_h );
    void draw( sf::RenderWindow &window );

	void fadein( int j = 1, int max = 255 );
	void fadeout( int j = 1, int min = 0 );
};