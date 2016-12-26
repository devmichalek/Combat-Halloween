#pragma once

#include "templates/state.h"
#include "world/moving_bg.h"
#include "hero/hero.h"
#include "world/brick.h"
#include "hero/kunai.h"
#include "hero/heart.h"
#include "hero/scope.h"

class Play_halloween
{
	State* state;
	Hero* hero;
	Moving_bg* bg;
	Brick* brick;
	Kunai* kunai;
	Heart* heart;
	Scope* scope;
	
public:

	Play_halloween();
    ~Play_halloween();
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
	
	void mechanics();
};