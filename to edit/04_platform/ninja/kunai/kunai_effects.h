#pragma once

#include "drawable/sprite.h"
#include <vector>
#include "04_platform/enemy/actions/expletive/slab.h"

class Kunai_effects
{
	int delay;
	vector <int> offset;
	vector <int> lines;
	vector <bool> active;
	vector <MySprite*> sprites;
	vector <Slab*> slabs;
	
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
	
	// Sound stuff.
	void turn();
	void turnOn();
	void turnOff();
	void setVolume( int v );
};