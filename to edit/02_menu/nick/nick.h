#pragma once

#include "drawable/sprite.h"
#include "drawable/text.h"

class Nick
{
	MyText text;
	MySprite label;
	
public:

	Nick();
	~Nick();
	void free();
	
	void load( int screen_w, int screen_h );
	void draw( sf::RenderWindow &window );
	void setNick();
	
	void fadein( int i = 1, int max = 255 );
	void fadeout( int i = 1, int min = 0 );
};