#pragma once

#include "templates/sprite.h"
#include "world/block.h"

class Brick
{
	int nr;
	MySprite* block;
	
	int width;
	int screen_w, screen_h;
	
	vector < Block* > envelope;
	vector < Block* > ladders;
	
public:
	
	void positioning();
	
	bool checkCollision( Rect* rect );
	bool checkBlockByPixel( Rect* rect );
	bool checkLadder( Rect* rect );
	
	
	Brick();
	~Brick();
	void free();

	void load( int screen_w, int screen_h, int number );
	void draw( sf::RenderWindow* &window );
	void drawBG( sf::RenderWindow* &window );
	
	int getScreenWidth();
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
};

