#pragma once

#include "templates/text.h"
#include "templates/sprite.h"

class Keyboard
{
	int text_nr;
	MyText* text;
	
public:

	Keyboard();
    ~Keyboard();

    void load( int right, int top );
    void draw( sf::RenderWindow &window );

	void fadein( int j = 1, int max = 255 );
	void fadeout( int j = 1, int min = 0 );
};