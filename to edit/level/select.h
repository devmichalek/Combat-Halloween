#pragma once

#include "level.h"

class Select
{
	int money;	// your money
	int* open;	// list of open levels
	
	int nr; // how many levels we have
	Level* level;
	int counter; // fadein gradually
	
public:
	
	Select();
	~Select();
	
	void load( int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window );
	void handle( sf::Event &event );
	
	void fadein( int i, int max );
	void fadeout( int i, int min );
	
	void turn();	// Turn on/off chunk
	void setVolume( sf::Uint8 volume );
};