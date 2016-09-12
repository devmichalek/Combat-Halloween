#pragma once

#include "templates/sprite.h"

class Music_volume
{
	Uint8 volume;
	MySprite green_bar;
	MySprite white_bar;
	
public:
	
	Music_volume();
	~Music_volume();
	
	void load( int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window, int range );
};