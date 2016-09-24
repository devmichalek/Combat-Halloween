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

	void fadein( int j, int max );
	void fadeout( int j, int min );
};