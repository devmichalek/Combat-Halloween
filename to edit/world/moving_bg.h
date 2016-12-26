#pragma once

#include "templates/sprite.h"

class Moving_bg
{
	MySprite sprite;
	int screen_w, screen_h;
	
	float vel;
	float x, y;
	
public:
	
	Moving_bg();
	~Moving_bg();
	void free();
	
	void load( string path, int w, int h );
	void draw( sf::RenderWindow* &window );
	void setXY( int posX, int posY );
	
	void fadein( int v = 1, int max = 255 );
	void fadeout( int v = 1, int min = 0 );
};