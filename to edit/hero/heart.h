#pragma once

#include "templates/sprite.h"

class Heart
{
	int nr;
	MySprite* fill;
	MySprite* frame;
	
	bool flag;
	
public:
	
	Heart();
	~Heart();
	void free();
	
	void load();
	void draw( sf::RenderWindow* &window );
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0x00 );
};