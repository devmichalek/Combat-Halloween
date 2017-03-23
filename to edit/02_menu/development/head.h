#pragma once

#include "drawable/sprite.h"
#include "drawable/text.h"
#include "02_menu/click.h"

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

	Head();
    ~Head();
	void free();

    void load( int type, int y );
    void draw( sf::RenderWindow* &window );
	void reloadText();
    void handle( sf::Event &event );
	
	void fadein( int i = 1, int max = 0xFF );
	void fadeout( int i = 1, int min = 0 );
	
	int getCost();
	void lock();
	void unlock();
	bool sellOut();
	void makeNought();
};