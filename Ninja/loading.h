#pragma once

#include "sprite.h"
#include "text.h"

class Loading
{
	MyText text;
	MySprite background;
	MySprite green_bar;
	MySprite white_bar;
	int state;
	
public:
	
	Loading();
	~Loading();
	
	bool load( int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window );
	int getState();
};