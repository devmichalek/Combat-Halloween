#pragma once

#include "drawable/sprite.h"
#include "block.h"
#include <vector>

class Plant
{
	vector <sf::Uint8> blocks;
public:

	sf::Uint8 nr;
	int startX, endX;
	int startY, endY;
	sf::Uint8 chance;
	bool bg;

	Plant();
	~Plant();
	
	void clear();
	void add( sf::Uint8 block );
	bool available( sf::Uint8 block );
	unsigned getSize();
	sf::Uint8 getBlocksNr( sf::Uint8 n );
};

class Veg_block :public Block
{
public:
	bool bg;
	using::Block::Block;
};

class Vegetation
{
	sf::Uint8 min;
	vector <Plant*> plants;
	vector <Veg_block*> blocks;
	vector <MySprite*> sprites;
	
	
	
public:
	
	Vegetation();
	~Vegetation();
	void free();
	
	void load( int type );
	void drawBG( sf::RenderWindow* &window, int screen_w );
	void draw( sf::RenderWindow* &window, int screen_w );
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	int strToInt( string s );
	unsigned getDistance( int v1, int v2 );
	void positioning( vector < Block* > blocks );
	
	void moveX( sf::Uint8 direction, float vel );
	int backToGrass( int add );
};