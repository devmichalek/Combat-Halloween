#pragma once

#include "templates/sprite.h"
#include "templates/text.h"

class Loading
{
	MyText text;	// text "loading"
	MySprite background;	// bg
	int state;		// show percents
	
	int counter;	// to set offsets
	int max;		// how many offset's
	MySprite progress_bar;	// animation
	
public:
	
	Loading();
	~Loading();
	void free(); // free
	
	void load( const int &screen_w, const int &screen_h );	// load textures
	void draw( sf::RenderWindow* &window );	// render textures
	
	int getState();
};