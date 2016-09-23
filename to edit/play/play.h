#pragma once

#include "templates/sprite.h"

class Play
{
	int state;
	
	MySprite background;
	
public:

	Play();
    ~Play();
    void free();
	
    void load( int screen_width, int screen_height );

    void handle( sf::Event &event );
    void draw( sf::RenderWindow* &window );
	
	bool isQuit();
	bool backToMenu();
};