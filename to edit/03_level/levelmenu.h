#pragma once

#include "sound/music.h"
#include "backtomenu.h"
#include "choice.h"
#include "character.h"
#include "worldsize.h"
#include "sound/sound.h"

class Level_menu
{
	int state;
	int screen_w, screen_h;
	
	// level menu objects
	Sound sound;
	MySprite* background;
	Music* music;
	Backtomenu* backtomenu;
	Choice* choice;
	Character* character;
	Worldsize* worldsize;
	
public:

	Level_menu();
    ~Level_menu();
    void free();
	
    void load( unsigned screen_w, unsigned screen_h );
    void handle( sf::Event &event );
    void draw( sf::RenderWindow* &window );
	
	
	int getState();
	Sound* getSound();
	void set( int state, Sound sound );
	bool isQuit();
	bool nextState();
	bool backToMenu();
	void reset();
	
	
	int getMap();
	int getCharacter();
	int getWorldsize();
};