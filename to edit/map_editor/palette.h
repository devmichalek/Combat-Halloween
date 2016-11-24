#pragma once

#include "templates/sprite.h"
#include "templates/text.h"

class Palette
{
	string folder_name;
	
	int nr;
	MySprite* block;

	MySprite bar;
	
	int which;
	int x, y;
	
public:
	
	Palette();
    ~Palette();
	void free();

    void load( int screen_w, int screen_h, int num );
    void draw( sf::RenderWindow* &window );
    void handle( sf::Event &event );
};