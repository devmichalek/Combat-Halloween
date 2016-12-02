#pragma once

#include "templates/sprite.h"
#include <vector>

class Block
{
public:
	int nr;
	int x, y;
	bool line;
	
	Block();
};

class Random_block
{
	int nr;
	MySprite* block;
	
	int width;
	int screen_w;
	int screen_h;
	
	vector <Block*> envelope;
	
public:
	
	Random_block();
	~Random_block();
	void free();
	
	void load( int screen_w, int screen_h, int number );
	void draw( sf::RenderWindow* &window );
	void positioning();
	
	bool checkCollisionH( int x, int w );
	bool checkCollisionV( int y, int h );
};