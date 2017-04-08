#pragma once

#include "drawable/sprite.h"

class Exit
{
	bool next;
	MySprite sprite;
	
public:
	
	Exit();
	~Exit();
	void free();
	void reset( int distance );
	
	void load( int width );
	void positioning( Rect* rect );
	
	// In action
	void moveX( sf::Uint8 direction, float vel );
	void undoFall( sf::Uint8 add );
	
	// Check, then turn into boss state.
	void checkHero( Rect* rect );
	bool nextState();
};