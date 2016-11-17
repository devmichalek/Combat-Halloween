#pragma once

#include "templates/sprite.h"
#include "templates/text.h"

class Palette
{
	string folder_name;
	
	int nr;
	MySprite* block;

	
	
public:
	
	Palette();
    ~Palette();
	void free();

    void load( int screen_w );
    void draw( sf::RenderWindow* &window );
    void handle( sf::Event &event );
};