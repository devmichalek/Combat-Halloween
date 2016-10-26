#pragma once

#include "templates/state.h"
#include "hero/hero.h"

class Play_halloween
{
	State* state;
	Hero* hero;
	MySprite* bg;
	
public:

	Play_halloween();
    ~Play_halloween();
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