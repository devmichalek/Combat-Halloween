#pragma once

#include "templates/sprite.h"
#include "menu/click.h"
#include "templates/text.h"

class Character :public Click
{
	MySprite one;
	MySprite two;
	
	MyText text;
	MyText information;
	
	int result;
	int ready;
	
	// Idle animation
	int how_many;
	int offset;
	
	// To move - animation
	int range;
	
public:
	
	Character();
    ~Character();
	void free();

    void load( int screen_w, int screen_h );
    void draw( sf::RenderWindow* &window );
    void handle( sf::Event &event );
	
	bool nextState();
	int getResult();
	
	void fadein( int j = 1, int max = 255 );
	void fadeout( int j = 1, int min = 0 );
	
	int getAlpha();
	bool move( int vel, int ran );	// move horizontal
};