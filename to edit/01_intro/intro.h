/**
    intro.h
    Purpose: class Intro - to show slides.

    @author Adrian Michalek
    @version 2016.10.12
	@email adrmic98@gmail.com
*/

#pragma once

#include "drawable/sprite.h"
#include "drawable/text.h"
#include <vector>

class Intro
{
	MySprite bg;		// background
	MySprite shuriken;	// shuriken image
	vector <MyText*> text;	// some sentences
	
	bool quit;
	
public:
	
	Intro();
	~Intro();
	void free();
	
	void load( unsigned screen_w, unsigned screen_h );	// load
	void draw( sf::RenderWindow* &window );				// render
	const bool& isQuit() const;		// tell us when we can stop rendering intro / accessor
};