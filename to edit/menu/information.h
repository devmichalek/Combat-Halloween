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

	void fadein( int v, int max );
	void fadeout( int v, int min );
};