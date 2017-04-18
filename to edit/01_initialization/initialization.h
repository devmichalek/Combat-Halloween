#pragma once

#include "nick_setter.h"
#include "nick_info.h"

class Initialization
{
	bool next;
	MySprite bg;
	Nick_setter nick_setter;
	Nick_info nick_info;
	
public:
	Initialization();
    ~Initialization();
    void free();
	
    void load( int screen_w, int screen_h );
    void handle( sf::Event &event );
    void draw( sf::RenderWindow* &window );

	bool nextState();
};