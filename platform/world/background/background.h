#pragma once

#include "drawable/sprite.h"
#include <vector>

class Background
{
	vector <MySprite*> sprites;
	
public:
	
	Background();
	~Background();
	void free();
	
	void load( int type, unsigned screen_w, unsigned screen_h );
	void draw( sf::RenderWindow* &window );
	void drawFront( sf::RenderWindow* &window ); // if its necessary
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	void mechanics( int x, int y );
	sf::Uint8 getAlpha();
	void setColor( sf::Color color );
};