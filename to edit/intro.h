#pragma once

#include "templates/sprite.h"
#include "templates/text.h"

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
	
	void load( int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window );
	bool isQuit();
};