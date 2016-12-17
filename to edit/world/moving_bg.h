#pragma once

#include "templates/sprite.h"

class Moving_bg
{
	MySprite one;
	MySprite two;
	
	float vel;
	sf::Uint8 direction;
	
	float x1, x2;
	
public:
	
	Moving_bg();
	~Moving_bg();
	void free();
	
	void load( string path );
	void draw( sf::RenderWindow* &window );
	void move( sf::Uint8 direction );
	
	void fadein( int v = 1, int max = 255 );
	void fadeout( int v = 1, int min = 0 );
};