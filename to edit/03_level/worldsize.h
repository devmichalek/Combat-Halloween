/**
    worldsize.h
    Purpose: class Worldsize - to choose size of world.

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
	
	float delay;
	sf::Uint8 blocks_value;
	sf::Uint8 blocks_times;
	
public:

	Worldsize();
	~Worldsize();

	void load( int screen_w, int screen_h );
	void handle( sf::Event &event );
	void draw( sf::RenderWindow &window );
	
	void fadein( int j = 1, int max = 255 );
	void fadeout( int j = 1, int min = 0 );
	
	int getResult();
	void reset();
	
	bool move( int vel, int scope );	// move horizontal
};