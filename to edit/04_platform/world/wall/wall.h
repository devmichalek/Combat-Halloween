#pragma once

#include "drawable/sprite.h"
#include "pug.h"

class Wall
{
	sf::Uint8 min;
	int width;
	int screen_w;
	
	vector <Pug*> blocks;
	vector <MySprite*> sprites;
	
public:
	
	// Basics.
	Wall();
	~Wall();
	void free();
	void reset( int distance );
	void load( int type, int width, int screen_w );
	void draw( sf::RenderWindow* &window );
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	
	// Creating
	void positioning( vector <Block*> blocks, int chance );
	
	// In action
	void moveX( sf::Uint8 direction, float vel );
	void undoFall( sf::Uint8 add );
	
	// Check collision.
	bool harm( Rect* rect );
	bool checkCollision( Rect* rect );
};