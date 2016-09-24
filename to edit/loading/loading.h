#pragma once

#include "templates/sprite.h"
#include "templates/text.h"

class Loading
{
	MyText text;
	MySprite background;
	int state;
	
	int counter;
	MySprite progress_bar;
	
public:
	
	Loading();
	~Loading();
	
	void load( int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window, int range );
	int getState();
};