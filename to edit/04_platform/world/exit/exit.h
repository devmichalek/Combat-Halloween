#pragma once

#include "drawable/sprite.h"
#include "04_platform/enemy/actions/expletive/slab.h"

class Exit
{
	int screen_w;
	bool next;
	float main_x;
	Slab rhythm;
	
public:
	
	Exit();
	~Exit();
	void free();
	void reset( int distance );
	
	void load( int width, int screen_w );
	void positioning( float right );
	
	// In action
	void moveX( sf::Uint8 direction, float vel );
	void undoFall( sf::Uint8 add );
	
	// Check, then turn into boss state.
	void checkHero( float x );
	bool nextState();
	
	// Sound stuff.
	void turnOn();
	void turnOff();
	void setVolume( int v );
};