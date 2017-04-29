/**
    scroll.h
    Purpose: class Scroll - scroll mechanics.

    @author Adrian Michalek
    @version 2017.03.30
	@email adrmic98@gmail.com
*/

#pragma once

#include "drawable/sprite.h"

class Scroll
{
	MySprite area;
	MySprite button;
	
	MySprite info;
	float info_x;
	
	bool handled;
	sf::Uint8 vel;
	bool moved;
	
public:
	
	Scroll();
    ~Scroll();
	void free();
	void reset();

    void load( unsigned screen_w, unsigned screen_h );
    void draw( sf::RenderWindow* &window );
	void handle( sf::Event &event );
	
	void fadein( int i = 1, int max = 255 );
	void fadeout( int i = 1, int min = 0 );
	
	// Extra
	bool isMoved();
	float getDistance();
};