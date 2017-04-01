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
	float point_scale_top;
	float foe_point_scale_top;
	float scale_vel;
	
	int point;
	int foe_point;
	
public:
	
	Scores();
	~Scores();
	void free();
	void reset();
	
	void load( int type, int screen_w );
	void draw( sf::RenderWindow* &window );
	void positioning( int chance );
	void mechanics();
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0x00 );
	
	void addPoint();
	void addFoePoint();
};