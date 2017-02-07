/**
    worldsize.h
    Purpose: class Worldsize - to set size of world.

    @author Adrian Michalek
    @version 2016.12.12
	@email adrmic98@gmail.com
*/

#pragma once

#include "drawable/text.h"
#include "drawable/sprite.h"
#include "02_menu/click.h"

class Worldsize :public Click
{
	MyText text;
	MyText blocks_text;
	MySprite white_bar;
	MySprite green_bar;
	
	// To move - animation
	int range;
	int blocks;
	bool keep;
	
	int min;
	int multiplier;
	int blocks_value;
	
public:

	Worldsize();
	~Worldsize();
	void free();
	void reset( unsigned screen_w, unsigned screen_h, int bot );


	void load( unsigned screen_w, unsigned screen_h, int bot );
	void handle( sf::Event &event );
	void draw( sf::RenderWindow &window );
	
	
	void fadein( int j = 1, int max = 255 );
	void fadeout( int j = 1, int min = 0 );
	
	int getResult();
	int getBot();
	bool move( int vel, int scope );	// move horizontal
};