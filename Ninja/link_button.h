#pragma once

#include "sprite.h"

class Link_button
{
    bool locked;
    string url;
    MySprite mySprite;


public:

    Link_button( string url, bool locked = false );
    ~Link_button();

    bool load( string path, int screen_w, int bot = 10 );
    void draw( RenderWindow &window );
    void handle( Event &event );
	
	int getBot();
};