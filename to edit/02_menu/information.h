#pragma once

#include "templates/text.h"

class Information
{
	int nr;
	MyText* text;
	
public:

	Information();
	~Information();
	void free();
	
	void load( int screen_h );
    void draw( sf::RenderWindow &window );

	void fadein( int v = 1, int max = 255 );
	void fadeout( int v = 1, int min = 0 );
};