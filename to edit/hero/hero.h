#pragma once

#include "templates/sprite.h"

class Hero
{
	int which;	// which activity is actual
	int offset;	// counter
	const volatile int off_const=0; 	// const how many offsets we have
	
	int nr;
	MySprite* sprite;
	
public:
	
	Hero();
	~Hero();
	void free();
	
	void load( int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window );
	void handle( sf::Event &event );
};