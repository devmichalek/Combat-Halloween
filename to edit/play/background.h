#pragma once

#include "templates/sprite.h"

class Background
{
	int nr;
	
	int active;
	int last;
	
	MySprite* one;
	MySprite* two;
	
public:
	
	Background();
	~Background();
	void free();
	
	void load( int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window );
	void handle( sf::Event &event );
	
	void change();
};