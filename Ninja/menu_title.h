#pragma once

#include "sprite.h"
#include "text.h"


class Menu_title
{
	MySprite belt;
	MyText title;
	
public:
	
	Menu_title();
    ~Menu_title();

    bool load( int screen_w );
    void draw( RenderWindow &window );
	
	int getBot();
	
	void fadein( int i, int max );
	void fadeout( int i, int min );
};