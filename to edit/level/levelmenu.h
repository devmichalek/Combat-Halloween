#pragma once

#include "templates/music.h"
#include "level/backtomenu.h"
#include "state.h"

class Level_menu
{
	State* state;
	MySprite* background;
	Music* music;
	Backtomenu* backtomenu;
	
public:

	Level_menu();
    ~Level_menu();
    void free();
	
    void load( int screen_w, int screen_h );

    void handle( sf::Event &event );
    void draw( sf::RenderWindow* &window );
	
	State* getState();
	void set( State* state );
	
	bool isQuit();
	bool nextState();
	bool backToMenu();
};