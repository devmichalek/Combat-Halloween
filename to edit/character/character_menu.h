#pragma once

#include "character/character.h"
#include "templates/music.h"
#include "level/backtomenu.h"
#include "state.h"

class Character_menu
{
	State* state;
	Character* character;
	MySprite* bg;
	Music* music;
	Backtomenu* backtomenu;

public:
	
	Character_menu();
    ~Character_menu();
    void free();
	
    void load( int screen_w, int screen_h );

    void handle( sf::Event &event );
    void draw( sf::RenderWindow* &window );
	
	State* getState();
	void set( State* state );
	
	bool isQuit();
	bool nextState();
	bool backToMenu();
	
	void reloadMusic();
	int getCharacter();
};