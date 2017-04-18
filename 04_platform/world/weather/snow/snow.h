#pragma once

#include "drawable/sprite.h"
#include <cstdint>
#include <vector>

class Snow
{
	int screen_w;
	int screen_h;
	int scope;
	
	vector <int16_t> alphas;
	vector <sf::CircleShape*> drops;
	
public:
	
	Snow();
	~Snow();
	void free();
	void reset();
	
	void load( int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window );
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	void mechanics();
};