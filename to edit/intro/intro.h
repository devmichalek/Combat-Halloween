#pragma once

#include "templates/sprite.h"
#include "templates/text.h"

class Intro
{
	MySprite bg;		// background
	MySprite shuriken;	// shuriken image
	MyText* text;
	
	int nr;		// how many text objects
	bool quit;
	
public:
	
	Intro();
	~Intro();
	
	void load( const int &screen_w, const int &screen_h );
	void draw( sf::RenderWindow* &window );
	bool isQuit();
};