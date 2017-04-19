#pragma once

#include "drawable/text.h"

class Nick_info
{
	MyText text;
	MyText text2;
	MyText text3;
	
public:
	
	Nick_info();
	~Nick_info();
	void free();
	
	void load( int screen_w, int screen_h );
    void draw( sf::RenderWindow* &window );
	
	void fadein( int i = 1, int max = 255 );
	void fadeout( int i = 1, int min = 0 );
};