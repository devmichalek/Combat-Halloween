#pragma once

#include "templates/sprite.h"
#include "templates/text.h"

class Choose_map
{
	int state;
	
	int nr;
	MySprite* sprite;
	
	MyText text;
	
public:

	Choose_map();
    ~Choose_map();
	void free();

    void load( int screen_w );
    void draw( sf::RenderWindow* &window );
    void handle( sf::Event &event );
	
	int chosenMap();
};