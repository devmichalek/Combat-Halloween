#pragma once

#include "templates/text.h"
#include "templates/sprite.h"
#include "menu/click.h"

class Worldsize :public Click
{
	MyText text;
	MyText blocks_text;
	MySprite white_bar;
	MySprite green_bar;
	
	// To move - animation
	int range;
	int blocks;
	
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
	
	bool move( int vel, int ran );	// move horizontal
};