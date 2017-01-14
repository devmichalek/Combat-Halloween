#pragma once

#include "drawable/sprite.h"
#include "block.h"
#include <cstdlib>
#include <time.h>
#include <vector>

class Plant
{
	vector <sf::Uint8> blocks;
	int startX, endX;
	int startY, endY;
	
public:

	Plant();
	~Plant();
	
	void clear();
	
	// mutators
	void add( sf::Uint8 block );
	void setX( int startX, int endX );
	void setY( int startY, int endY );
	
	// getters
	bool available( sf::Uint8 block );
	int getX();
	int getY();
};

class Vegetation
{
	sf::Uint8 world_type;
	sf::Uint8 min, max;
	
	vector <Plant*> plants;
	
public:

	Vegetation();
	~Vegetation();
	void free();
	
	void load( int type, vector < Block* > blocks );
	void draw( sf::RenderWindow* &window );
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
};