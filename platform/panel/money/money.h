/**
    money.h
    Purpose: class Money responsible for drawing coins, coin mechanis etc.

    @author Adrian Michalek
    @version 2017.02.14
	@email adrmic98@gmail.com
*/

#pragma once

#include "drawable/sprite.h"
#include "drawable/text.h"

class Money
{
	MyText text;
	MySprite grey;
	MySprite coin;
	
	int base;
	int bank;
	
	int offset;
	int delay;
	int line;
	
public:
	
	Money();
	~Money();
	void free();
	void reset();
	
	void load( int screen_w );
	void draw( sf::RenderWindow* &window );
	void mechanics();
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0x00 );
	
	void setText();
	void saveMoney();
	void loadMoney();
	void add( int amount );
	int getEarnedMoney();
};