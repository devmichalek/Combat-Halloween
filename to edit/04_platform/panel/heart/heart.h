#pragma once

#include "drawable/sprite.h"
#include <vector>

class Heart_bit
{
public:
	
	int x, y;
	int alpha;
	
	Heart_bit();
	~Heart_bit();
	void free();
};

class Heart
{
	int max;
	int life;
	
	vector <Heart_bit*> fill_bits;
	vector <Heart_bit*> grey_bits;
	vector <Heart_bit*> frame_bits;
	
	MySprite fill;
	MySprite grey;
	MySprite frame;
	

public:
	
	Heart();
	~Heart();
	void free();
	void reset();
	
	void load();
	void draw( sf::RenderWindow* &window );
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0x00 );
	
	void harm( int damage );
	bool isDead();
	int strToInt( string s );
};