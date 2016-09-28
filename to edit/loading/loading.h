#pragma once

#include "templates/sprite.h"
#include "templates/text.h"

class Loading
{
	MyText text;	// "loading"
	MySprite background;	// bg
	int state;		// show percents
	
	int counter;	// to set offsets
	int max;		// how many offset's
	MySprite progress_bar;
	
public:
	
	Loading();
	~Loading();
	void free();
	
	void load( const int &screen_w, const int &screen_h );
	void draw( sf::RenderWindow* &window );
	
	int getState();
};