#pragma once

#include "sound/sound.h"
#include "04_platform/background/moving_bg.h"
#include "04_platform/hero/hero.h"
#include "04_platform/world/brick.h"
#include "04_platform/hero/kunai.h"
#include "04_platform/hero/heart.h"
#include "04_platform/hero/scope.h"
#include "04_platform/greenery/greenery.h"
#include "04_platform/ladder/ladder.h"
#include "04_platform/wall/wall.h"
#include "04_platform/background/bg.h"

class Play_desert
{
	int state;
	string info;
	
	int screen_w;
	int screen_h;
	
	// Play wood objects
	Sound sound;
	Hero* hero;
	Moving_bg* moving_bg;
	Brick* brick;
	Kunai* kunai;
	Heart* heart;
	Scope* scope;
	Greenery* greenery;
	Ladder* ladder;
	Wall* wall;
	Bg* bg;
	
public:

	Play_desert();
    ~Play_desert();
    void free();
	void reset();
	
    void load( int screen_w, int screen_h );
    void handle( sf::Event &event );
    void draw( sf::RenderWindow* &window );
	
	bool positioning( int size, int flatness, int type );
	string getInfo();
	
	bool nextState();
	bool backToLevel();
	void mechanics();
};