#pragma once

#include "drawable/text.h"

class Scores
{
	MyText text;
	
	int result;
	int last_result;
	int screen_w;
	
	float scale;
	float scale_bot;
	float scale_top;
	float scale_vel;
	
public:
	
	Scores();
	~Scores();
	void free();
	void reset();
	
	void load( int screen_w );
	void draw( sf::RenderWindow* &window );
	void mechanics();
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0x00 );
	
	void add( int amount );
};