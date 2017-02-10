#pragma once

#include "04_platform/world/brick/block.h"
#include "drawable/sprite.h"
#include <vector>

class Water
{
	sf::Uint8 min;
	int width;
	int screen_w;
	int screen_h;
	
	vector <Block*> waterblocks;
	vector <MySprite*> sprites;
	
public:
	
	// Basics.
	Water();
	~Water();
	void free();
	void reset( int distance );
	void load( int type, int width, int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window );
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );

	// Support.
	void addBlock( int n, int x, int y );
	
	// In action
	void moveX( sf::Uint8 direction, float vel );
	void undoFall( sf::Uint8 add );
	
	// Creating.
	void createWater( vector <Block*> b1, vector <Block*> b2, int right );	// Add water.
	
	// Collision detection.
	bool checkCollision( Rect* rect );
};