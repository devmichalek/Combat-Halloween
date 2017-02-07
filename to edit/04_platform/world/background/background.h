#pragma once

#include "drawable/sprite.h"

class Background
{
	int screen_w;
	int screen_h;
	
	MySprite sprite;
	
public:
	
	Background();
	~Background();
	void free();
	void reset( int x, int y );
	
	void load( int type, int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window );
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	void setPosition( int x, int y );
	sf::Uint8 getAlpha();
};