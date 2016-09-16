#pragma once

#include "templates/sprite.h"
#include "templates/text.h"


class Title
{
	MySprite belt;
	MyText title;
	
public:
	
	Title();
    ~Title();

    void load( int screen_w );
    void draw( sf::RenderWindow &window );
	
	int getBot();
	
	void fadein( int i, int max );
	void fadeout( int i, int min );
};