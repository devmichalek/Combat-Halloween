#pragma once

#include "templates/sprite.h"
#include "templates/text.h"

class Loading
{
	MyText text;			// text "loading"
	MySprite bg;			// background
	sf::Uint8 state;		// show percents
	
	mutable sf::Uint8 counter;	// to set offsets
	sf::Uint8 max;			// how many offset's
	MySprite progress_bar;	// animation
	
public:
	
	Loading();
	~Loading();
	void free();
	
	void load( const int &screen_w, const int &screen_h );		// load textures
	void draw( sf::RenderWindow* &window );						// render textures
	
	const sf::Uint8& getState() const; 								// getter
};