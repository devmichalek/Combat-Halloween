#pragma once

#include "drawable/sprite.h"
#include <vector>

class Background
{
	int screen_w;
	int screen_h;
	
	vector <MySprite*> sprites;
	
public:
	
	Background();
	~Background();
	void free();
	void reset( int x, int y );
	
	void load( int type, int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window );
	void drawFront( sf::RenderWindow* &window ); // if its necessary
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	void mechanics( int x, int y );
	sf::Uint8 getAlpha();
	void setColor( sf::Color color );
	
	int getX();
	int getY();
};