#pragma once

#include "drawable/sprite.h"
#include "wallblock.h"

class Wall
{
	vector <MySprite*> sprites;
	vector <WallBlock*> blocks;
	
public:
	
	// Basics.
	Wall();
	~Wall();
	void free();
	void reset( int distance );
	
	void load( int type );
	void draw( sf::RenderWindow* &window, int screen_w );
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	
	// Creating
	void positioning( vector <Block*> blocks, int l, int r );
	
	// In action
	void moveX( sf::Uint8 direction, float vel );
	void backToGrass( int add );
	
	bool allowHarm( int x1, int x2 );
	bool harm( Rect* rect, int screen_w );
	bool checkCollision( Rect* rect, int screen_w );
};