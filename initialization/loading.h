#pragma once

#include "own/text.h"
#include "own/sprite.h"
#include <SFML/Graphics/RenderWindow.hpp>

class Loading
{
	int w, h;
	bool ready;
	
	MyText text;			// text "loading"
	sf::Uint8 state;		// show percents
	
	sf::Uint8 counter;		// to set offsets
	sf::Uint8 max;			// how many offset's
	MySprite progress_bar;	// animation
	
public:
	
	// Basics.
	Loading();
	~Loading();
	void free();
	
	void load( unsigned screen_w, unsigned screen_h );	// load textures
	void draw( sf::RenderWindow* &window, double elapsedTime );				// render textures
	
	// In addition.
	const sf::Uint8& getState() const; 		// getter
	bool isReady();
	void beReady();
};