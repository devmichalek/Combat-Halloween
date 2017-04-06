#pragma once

#include "skull.h"
#include <vector>

class Skulls
{
	vector <Skull*> skulls;
	
public:
	
	Skulls();
	~Skulls();
	void free();
	void reset();
	
	void load( int type, int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window );
	
	void fadein( int j = 1, int max = 0xFF );
	void fadeout( int j = 1, int min = 0 );
	
	// In action
	void moveX( sf::Uint8 d, float v );
	void undoFall( sf::Uint8 add );
	void mechanics( int x, int y );
	void setColor( sf::Color color );
};