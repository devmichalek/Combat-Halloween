#pragma once

#include "drawable/sprite.h"
#include "drawable/text.h"

class Money_panel
{
	MySprite grey;
	MySprite coin;
	MyText text;
	
	int base;
	int bank;
	
	int offset;
	int delay;
	int line;
	
public:
	
	Money_panel();
	~Money_panel();
	void free();
	void reset();
	
	void load( int screen_w );
	void draw( sf::RenderWindow* &window );
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0x00 );
	
	void setText();
	void saveMoney();
	void loadMoney();
	void add( int amount );
	int strToInt( string s );
};