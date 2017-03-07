/**
    heart.h
    Purpose: class Heart responsible for drawing hearts, heart mechanis etc.

    @author Adrian Michalek
    @version 2017.03.06
	@email adrmic98@gmail.com
*/

#pragma once

#include "drawable/sprite.h"
#include <vector>
#include "04_platform/panel/heart/heart_bit.h"

class Heart
{
	int max;	// Max amount of hearts.
	int life;	// Life.
	
	// Heart bit contain x, y and alpha values.
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
};