#pragma once

#include "drawable/sprite.h"
#include "drawable/text.h"

class Show_scores
{
	int screen_w;
	int screen_h;
	int max, min;
	int n;
	int vel;
	MyText text;
	MyText summary;
	
public:
	
	Show_scores();
	~Show_scores();
	void free();
	void reset();
	
	void load( int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window );
	void mechanics();
	void set( int scores );
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
};