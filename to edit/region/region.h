#pragma once

#include "templates/sprite.h"

class Region
{
	MySprite picture;
	int focus;
	
	int x, y; // real x and y
	
public:
	
	Region();
	~Region();
	void free();
	
	void load( string path );
	void draw( sf::RenderWindow* &window );
	void handle( sf::Event &event );
	
	void fadein( int v = 1, int max = 255 );
	void fadeout( int v = 1, int min = 0 );
};