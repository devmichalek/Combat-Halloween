#pragma once

#include "sound/sound.h"
#include "04_platform/world/moving_bg.h"
#include "04_platform/hero/hero.h"
#include "04_platform/world/brick.h"
#include "04_platform/hero/kunai.h"
#include "04_platform/hero/heart.h"
#include "04_platform/hero/scope.h"
#include "04_platform/world/greenery.h"
#include "04_platform/world/ladder.h"

class Play_winter
{
	int state;
	string info;
	
	int screen_w;
	int screen_h;
	
	// Play wood objects
	Sound sound;
	Hero* hero;
	Moving_bg* bg;
	Brick* brick;
	Kunai* kunai;
	Heart* heart;
	Scope* scope;
	Greenery* greenery;
	Ladder* ladder;
	
public:

	Play_winter();
    ~Play_winter();
    void free();
	void reset();
	
    void load( int screen_w, int screen_h );
    void handle( sf::Event &event );
    void draw( sf::RenderWindow* &window );
	
	bool positioning( int size, int type );
	string getInfo();
	
	bool nextState();
	bool backToLevel();
	void mechanics();
};