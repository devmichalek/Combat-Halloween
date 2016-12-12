#pragma once

#include "templates/state.h"
#include "wood/moving_bg.h"
#include "hero/hero.h"
#include "wood/random_block.h"
#include "hero/kunai.h"
#include "hero/heart.h"
#include "enemy/golem.h"

class Play_desert
{
	State* state;
	Hero* hero;
	Moving_bg* bg;
	Random_block* random_block;
	Kunai* kunai;
	Heart* heart;
	Golem* golem;
	
public:

	Play_desert();
    ~Play_desert();
    void free();
	
    void load( int screen_w, int screen_h );
	void setHero( int screen_w, int screen_h, int type );

    void handle( sf::Event &event );
    void draw( sf::RenderWindow* &window );
	
	State* getState();
	void set( State* state );
	
	bool isQuit();
	bool nextState();
	bool backToLevel();
	
	void reloadMusic();
};