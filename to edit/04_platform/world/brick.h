#pragma once

#include "drawable/sprite.h"
#include "block.h"
#include "ladder.h"

class Brick
{
	vector <MySprite*> block;
	vector <Block*> blocks;
	vector <Block*> bg_blocks;
	
	int width;
	int screen_w;
	int screen_h;
	
	int left, right;
	
	int lastGrass;
	int fallenX;
	
public:
	
	Brick();
	~Brick();
	void free();
	
	void load( int screen_w, int screen_h, int nr, int type );
	void draw( sf::RenderWindow* &window );
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );

	
	void addBlock( int chosen, int x_width, int floor );
	bool randFloor( bool &top, sf::Uint8 floor, sf::Uint8 &new_floor );
	void fill( int a, int n );	//  Fill from left to right
	
	vector <Plank*> bot_islands( int w2, int h2, unsigned size );	// we have send size because we want to have it before islands
	vector <Plank*> top_islands( int w2, int h2 );
	vector <Plank*> positioning( int size, int w1, int h1, int w2, int h2 );
	
	// bool checkCollision( Rect* rect );
	bool checkBlockByPixel( Rect* rect );
	
	sf::Uint8 moveX( sf::Uint8 direction, float vel );
	sf::Uint8 getWidth();
	vector < Block* > getBlocks();
	
	void findLastGrass( Rect* rect );
	int getLastGrassY();
	int getLastGrassX();
	void setNewX( int heroX );
	int backToGrass();
};

