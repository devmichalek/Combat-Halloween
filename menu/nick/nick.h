/**
    nick.h
    Purpose: class Nick to show nick in menu state.

    @author Adrian Michalek
    @version 2017.03.27
	@email adrmic98@gmail.com
*/

#pragma once

#include "drawable/sprite.h"
#include "drawable/text.h"

class Nick
{
	MyText text;
	MySprite label;
	MySprite info;
	
	bool show;
	
public:
	
	// Basics.
	Nick();
	~Nick();
	void free();
	
	void load( unsigned screen_w, unsigned screen_h, float x, float y );
	void draw( sf::RenderWindow &window );
	void drawInfo( sf::RenderWindow &window );
	
	void fadein( int i = 1, int max = 255 );
	void fadeout( int i = 1, int min = 0 );
	
	// In addition.
	void setNick();
	
	void setShow();
};