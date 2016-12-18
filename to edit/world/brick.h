#pragma once

#include "templates/sprite.h"
#include "world/block.h"
#include "world/ladder.h"

class Brick
{
	int nr;
	MySprite* block;
	MySprite ladder;
	
	int width;
	int screen_w, screen_h;
	
	vector < Block* > blocks;
	vector < Ladder* > ladders;
	
public:
	
	void positioning();
	
	bool checkCollision( Rect* rect );
	bool checkBlockByPixel( Rect* rect );
	bool checkLadder( Rect* rect );
	
	
	Brick();
	~Brick();
	void free();

	void load( int screen_w, int screen_h, int nr, int type );
	void draw( sf::RenderWindow* &window );
	void drawBG( sf::RenderWindow* &window );
	
	int getScreenWidth();
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
};

