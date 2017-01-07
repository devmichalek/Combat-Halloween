#pragma once

#include "templates/text.h"

class Worldsize
{
	
	MyText text;
	
public:

	Worldsize();
	~Worldsize();

	void load( int screen_w, int screen_h );
	void handle( sf::Event &event );
	void draw( sf::RenderWindow &window );
	
	void fadein( int j = 1, int max = 255 );
	void fadeout( int j = 1, int min = 0 );
	
	int getResult();
	void reset();
	
	bool move( int vel, int ran );	// move horizontal
};