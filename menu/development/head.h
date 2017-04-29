/**
    head.h
    Purpose: class Head - it's a part of head group (headdeck), represents 1 particular hero who can be buy

    @author Adrian Michalek
    @version 2017.04.07
	@email adrmic98@gmail.com
*/

#pragma once

#include "drawable/sprite.h"
#include "drawable/text.h"
#include "menu/click.h"

class Head :public Click
{
	int cost;
	int type;
	int kind;
	int state;
	bool locked;
	
	MySprite sprite;
	MySprite button;
	MyText name;
	MyText specs;
	MyText cost_text;

public:
	
	// Basics.
	Head();
    ~Head();
	void free();
	
	void load( int type, unsigned screen_w, float y );
	void draw( sf::RenderWindow* &window );
	void handle( sf::Event &event );
	
	void fadein( int i = 1, int max = 0xFF );
	void fadeout( int i = 1, int min = 0 );
	
	// Extra
	void reloadText();
	int getCost();
	void lock();
	void unlock();
	bool sellOut();
	void makeNought();
};