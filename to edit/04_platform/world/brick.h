#pragma once

#include "drawable/sprite.h"
#include "block.h"
#include "ladder.h"


class Special_ladder
{
public:
	
	int x, y;
	bool used;
	
	Special_ladder();
	~Special_ladder();
};

class Brick
{
	int nr;
	MySprite* block;
	
	int ladder_nr;
	MySprite* ladder;
	
	int width;
	int screen_w, screen_h;
	
	int left, right;
	int world_type;
	
	vector < Block* > blocks;
	vector < Ladder* > ladders;
	
	Special_ladder red, white, black;
	
public:
	
	void addBlock( int chosen, int x_width, int floor );
	void addLadder( int x, int y );
	
	bool randFloor( bool &top, sf::Uint8 floor, sf::Uint8 &new_floor );
	void fill( int a, int n );
	void islands();
	void positioning( int size );
	
	
	bool checkCollision( Rect* rect );
	bool checkBlockByPixel( Rect* rect );
	bool checkLadder( Rect* rect );
	
	sf::Uint8 moveX( sf::Uint8 direction, float vel );
	sf::Uint8 getWidth();
	bool isBlock( int x, int y );
	
	
	Brick();
	~Brick();
	void free();

	void load( int screen_w, int screen_h, int nr, int type );
	void draw( sf::RenderWindow* &window );
	void drawLadders( sf::RenderWindow* &window );
	
	int getScreenWidth();
	int getScreenHeight();
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
};

