#pragma once

#include "templates/sprite.h"

class Hero
{
	int which;	// which activity is actual
	int offset;	// counter
	int delay;
	const volatile int off_const=0; 	// const how many offsets we have
	
	int nr;
	MySprite* sprite;
	
	enum Activity
	{
		IDLE = 0,
		RUN,
		THROW,
		ATTACK,
		SLIDE,
		CLIMB,
		GLIDE,
		JUMP,
		JUMP_ATTACK,
		JUMP_THROW,
		DEAD
	};
	
public:
	
	Hero();
	~Hero();
	void free();
	
	void load( int screen_w, int y );
	void draw( sf::RenderWindow* &window );
	void handle( sf::Event &event );
	
	void fadein( int v = 1, int max = 255 );
	void fadeout( int v = 1, int min = 0 );
};