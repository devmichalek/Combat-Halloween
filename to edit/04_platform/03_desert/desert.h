#pragma once

// Sound
#include "sound/sound.h"

// Hero stuff
#include "04_platform/hero/hero.h"
#include "04_platform/hero/kunai.h"
#include "04_platform/hero/scope.h"

// Panel stuff
#include "04_platform/panel/heart/heart.h"
#include "04_platform/panel/money/money_panel.h"

// World stuff
#include "04_platform/world/brick/brick.h"
#include "04_platform/world/background/effect.h"
#include "04_platform/world/background/background.h"
#include "04_platform/world/islands/islands.h"
#include "04_platform/world/wall/wall.h"
#include "04_platform/world/ladder/ladder.h"
#include "04_platform/world/greenery/greenery.h"
#include "04_platform/world/background/day.h"


// Enemy
#include "04_platform/enemy/mine/mine_factory.h"
#include "04_platform/enemy/factory/factory.h"
#include "04_platform/enemy/skeleton/skeleton.h"

class Desert
{
	int state;
	string info;
	
	int width;
	int screen_w;
	int screen_h;
	
	// sound
	Sound sound;
	
	// hero
	Hero* hero;
	Kunai* kunai;
	Scope* scope;
	
	// panel
	Heart* heart;
	Money_panel* money_panel;
	
	// world
	Brick* brick;
	Effect* effect;
	Background* background;
	Islands* islands;
	Wall* wall;
	Ladder* ladder;
	Greenery* greenery;
	Day* day;
	
	// enemy
	Mine_factory* mine_factory;
	Factory <Skeleton> skeleton_factory;
	
	
public:

	Desert();
    ~Desert();
    void free();
	void reset();
	
    void load( int screen_w, int screen_h, unsigned FPS );
    void handle( sf::Event &event );
    void draw( sf::RenderWindow* &window );
	
	bool positioning( int type, int size, int flatness, int difficulty );
	string getInfo();
	
	bool nextState();
	bool backToLevel();
	void mechanics();
};