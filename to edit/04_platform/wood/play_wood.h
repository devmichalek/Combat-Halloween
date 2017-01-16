#pragma once

#include "sound/sound.h"
#include "04_platform/world/moving_bg.h"
#include "04_platform/hero/hero.h"
#include "04_platform/world/brick.h"
#include "04_platform/hero/kunai.h"
#include "04_platform/hero/heart.h"
#include "04_platform/hero/scope.h"
#include "04_platform/world/vegetation.h"

class Play_wood
{
	int state;
	
	// Play wood objects
	Sound* sound;
	Hero* hero;
	Moving_bg* bg;
	Brick* brick;
	Kunai* kunai;
	Heart* heart;
	Scope* scope;
	Vegetation* vegetation;
		
public:

	Play_wood();
    ~Play_wood();
    void free();
	
    void load( int screen_w, int screen_h );
    void handle( sf::Event &event );
    void draw( sf::RenderWindow* &window );
	
	
	void setHero( int screen_w, int screen_h, int type );
	void setWorldsize( int size );
	
	
	int getState();
	Sound* getSound();
	void set( int state, Sound* sound );
	bool isQuit();
	bool nextState();
	bool backToLevel();
	void reloadMusic();
	
	
	void mechanics();
};