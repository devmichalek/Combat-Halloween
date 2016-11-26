#pragma once

#include "templates/sprite.h"
#include "templates/text.h"

class SaveLog
{
	MySprite bar;
	MyText basic;
	MyText edit;
	
	string edit_s;
	bool action;
	
public:
	
	SaveLog();
    ~SaveLog();
	void free();

    void load( int screen_w, int screen_h, string folder );
    void draw( sf::RenderWindow* &window );
    void handle( sf::Event &event );
};