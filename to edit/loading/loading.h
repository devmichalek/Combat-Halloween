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
	
	void load( const int &screen_w, const int &screen_h );
	void draw( sf::RenderWindow* &window );
	int getState();
};