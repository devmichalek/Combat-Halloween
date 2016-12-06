#pragma once

#include "templates/sprite.h"
#include "templates/text.h"

class Intro
{
	MySprite bg;		// background
	MySprite shuriken;	// shuriken image
	MyText* text;	// some sentences
	
	sf::Uint8 nr;		// how many text objects
	bool quit;
	
public:
	
	Intro();
	~Intro();
	void free();
	
	void load( const int &screen_w, const int &screen_h );	// load
	void draw( sf::RenderWindow* &window );	// render
	const bool& isQuit() const;	// tell us when we can stop rendering intro / accessor
};