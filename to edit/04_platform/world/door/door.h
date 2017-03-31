#pragma once

#include "drawable/sprite.h"

class Door
{
	bool next;
	MySprite sprite;
	
public:
	
	Door();
	~Door();
	void free();
	void reset( int distance );
	
	void load( int type );
	void draw( sf::RenderWindow* &window );
	void positioning( Rect* rect );
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	// In action
	void moveX( sf::Uint8 direction, float vel );
	void undoFall( sf::Uint8 add );
	void setColor( sf::Color color );
	
	// Check, then turn into boss state.
	void checkHero( Rect* rect );
	bool nextState();
};