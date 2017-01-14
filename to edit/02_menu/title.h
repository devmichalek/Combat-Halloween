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

    void load( const int& screen_w );
    void draw( sf::RenderWindow &window );
	
	const int& getBot();	// accessor
	
	void fadein( int i = 1, int max = 255 );
	void fadeout( int i = 1, int min = 0 );
};