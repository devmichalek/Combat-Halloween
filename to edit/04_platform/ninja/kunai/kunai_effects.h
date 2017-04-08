#pragma once

#include "drawable/sprite.h"
#include <vector>

class Kunai_effects
{
	int delay;
	vector <float> x;
	vector <int> offset;
	vector <int> lines;
	vector <bool> active;
	vector <MySprite*> sprites;
	
public:
	
	Kunai_effects();
	~Kunai_effects();
	void free();
	
	void load( int which );
	void draw( sf::RenderWindow* &window );
	void mechanics();
	
	void fadein( int v, int max = 0xFF );
	void fadeout( int v, int min = 0 );
	
	void run( int which, Rect* rect );
	
	// In action
	void moveX( float vel );
	void undoFall( sf::Uint8 add );
	void setColor( sf::Color color );
};