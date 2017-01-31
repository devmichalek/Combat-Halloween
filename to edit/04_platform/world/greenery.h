#pragma once

#include "drawable/sprite.h"
#include "greenblock.h"
#include "plant.h"

class Greenery
{
	sf::Uint8 min;
	vector <Plant*> plants;
	vector <MySprite*> sprites;
	vector <GreenBlock*> blocks;
	
public:
	
	Greenery();
	~Greenery();
	void free();
	void reset( int distance );
	void load( int type );
	void draw( sf::RenderWindow* &window, int screen_w );
	void drawBG( sf::RenderWindow* &window, int screen_w );
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	
	int to_int( string s );
	unsigned getDistance( int v1, int v2 );
	void positioning( vector < Block* > blocks );
	
	void moveX( sf::Uint8 direction, float vel );
	void backToGrass( int add );
};