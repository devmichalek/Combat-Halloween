#pragma once

#include "sprite.h"
#include "text.h"

class Intro
{
	MySprite bg;	// background
	MySprite shuriken;
	
	int nr;		// how many text objects
	MyText* text;
	
	bool quit;
	
public:
	
	Intro();
	~Intro();
	
	bool load( int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window );
	bool isQuit();
};