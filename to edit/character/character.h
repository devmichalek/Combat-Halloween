#pragma once

#include "templates/sprite.h"
#include "menu/parentchunk.h"
#include "templates/text.h"

class Character :public Parentchunk
{
	MySprite one;
	MySprite two;
	
	MyText one_t;
	MyText two_t;
	
	int result;
	bool ready;
	bool focus2;
	
public:
	
	Character();
    ~Character();
	void free();

    void load( int screen_w, int screen_h );
    void draw( sf::RenderWindow* &window );
    void handle( sf::Event &event );
	
	bool nextState();
	int getResult();
	
	void fadein( int j, int max );
	void fadeout( int j, int min );
	
	int getAlpha();
};