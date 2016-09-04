#pragma once

#include "text.h"
#include "sprite.h"

class Game_timer
{
	MySprite one;
	MySprite two;
	
	MyText text;
	float max;
	float counter;
	bool flag;
	bool paused;
	
public:
	
	Game_timer();
	~Game_timer();
	void free();
	
	bool load( int screen_w );
	void count( int screen_w );
	void draw( sf::RenderWindow &window );
	void handle( sf::Event &event );
	
	bool isPaused();
	bool newWall();
	
	void fadein( int i = 1, int max = 0xFF );
	void fadeout( int i = 1, int min = 0 );
};