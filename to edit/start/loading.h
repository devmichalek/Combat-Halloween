#pragma once

#include "templates/sprite.h"
#include "templates/text.h"

class Loading
{
	MyText text;
	MySprite* background;
	MySprite* green_bar;
	MySprite* white_bar;
	int state;
	
public:
	
	Loading();
	~Loading();
	
	void load( int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window, int range );
	int getState();
};