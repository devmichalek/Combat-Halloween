#pragma once

#include "drawable/sprite.h"
#include "drawable/text.h"
#include "02_menu/click.h"

class Cube :public Click
{
	MySprite down;
	MySprite left;
	MySprite paper;
	MySprite cube;
	
	MyText flatness;
	MyText worldSize;
	
	int flatness_value;
	int worldSize_value;
	
	int offset;
	int delay;
	int line;
	
	// Moving animation
	int range;
	bool keep;
	
public:

	Cube();
	~Cube();
	void free();
	void reset( int left, int bot );
	void load( int left, int bot );
	void handle( sf::Event &event );
	void draw( sf::RenderWindow &window );
	void fadein( int j = 1, int max = 255 );
	void fadeout( int j = 1, int min = 0 );
	
	void setFlatness( int value );
	void setWorldSize( int value );
	
	
	bool move( int vel, int scope );	// move horizontal
	int getFlatness();
	int getWorldSize();
	
	int getTop();
	int getRight();
};