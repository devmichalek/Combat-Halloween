/**
    level.h
    Purpose: class Level - huge object which contains stuff drawable in level state.

    @author Adrian Michalek
    @version 2016.12.20
	@email adrmic98@gmail.com
*/

#pragma once

#include "sound/sound.h"
#include "sound/music.h"
#include "backtomenu.h"
#include "choice.h"
#include "character.h"
#include "cube.h"
#include "difficulty.h"

class Level
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
	Cube* cube;
	Difficulty* difficulty;
	
public:

	Level();
    ~Level();
    void free();
	
    void load( unsigned screen_w, unsigned screen_h );
	void loadCharacter();
    void handle( sf::Event &event );
    void draw( sf::RenderWindow* &window );
	
	void setSound();
	bool isQuit();
	bool nextState();
	bool backToMenu();
	void reset();
	void reloadMusic();
	
	
	int getWorld();
	int getCharacter();
	int getWorldsize();
	int getFlatness();
	int getDifficulty();
};