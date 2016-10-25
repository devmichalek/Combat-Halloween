#pragma once

#include "templates/state.h"
#include "hero/hero.h"

class Play_desert
{
	State* state;
	Hero* hero;
	
public:

	Play_desert();
    ~Play_desert();
    void free();
	
    void load( int screen_w, int screen_h );

    void handle( sf::Event &event );
    void draw( sf::RenderWindow* &window );
	
	State* getState();
	void set( State* state );
	
	bool isQuit();
	bool nextState();
	bool backToLevel();
	
	void reloadMusic();
};