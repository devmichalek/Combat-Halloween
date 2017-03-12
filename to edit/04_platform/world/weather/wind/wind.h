#pragma once

#include "drawable/sprite.h"
#include <cstdint>

class Wind
{
	int screen_w;
	int screen_h;
	int scope;
	
	vector <int16_t> ways;
	vector <int16_t> alphas;
	vector <sf::ConvexShape*> drops;
	
public:
	
	Wind();
	~Wind();
	void free();
	void reset();
	
	void create( int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window );
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	void mechanics();
	void moveX( sf::Uint8 direction, float vel );
	void undoFall( sf::Uint8 add );
};