#pragma once

#include "templates/sprite.h"

class BG_map
{
	int which;
	
	int nr;
	MySprite* sprite;
	
public:
	
	BG_map();
	~BG_map();
	void free();
	
	void load( int screen_w, int y );
	void draw( sf::RenderWindow* &window );
	void handle( sf::Event &event );
	
	void fadein( int v = 1, int max = 255 );
	void fadeout( int v = 1, int min = 0 );
};