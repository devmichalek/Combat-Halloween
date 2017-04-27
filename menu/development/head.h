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
	int y_state;
	float scale;
	
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
	
	void load( int type, int y );
	void draw( sf::RenderWindow* &window );
	void handle( sf::Event &event, int r_x, int r_y );
	
	void fadein( int i = 1, int max = 0xFF );
	void fadeout( int i = 1, int min = 0 );
	
	// Extra
	void reloadText();
	int getCost();
	void lock();
	void unlock();
	bool sellOut();
	void makeNought();
	
	// Window.
	void setScale( float s_x, float s_y );
	void setView( int w, int h, int r_x, int r_y );
};