#pragma once

// Sound
#include "sound/sound.h"

// Hero stuff
#include "04_platform/hero/hero.h"
#include "04_platform/hero/kunai.h"
#include "04_platform/hero/heart.h"
#include "04_platform/hero/scope.h"

// World stuff
#include "04_platform/world/brick/brick.h"
#include "04_platform/world/background/effect.h"
#include "04_platform/world/background/background.h"
#include "04_platform/world/islands/islands.h"
#include "04_platform/world/wall/wall.h"
#include "04_platform/world/ladder/ladder.h"
#include "04_platform/world/greenery/greenery.h"

// Enemy
#include "04_platform/enemy/mine/mine_factory.h"

class Halloween
{
	int state;
	string info;
	
	int screen_w;
	int screen_h;
	
	// sound
	Sound sound;
	
	// hero
	Hero* hero;
	Kunai* kunai;
	Heart* heart;
	Scope* scope;
	
	// world
	Brick* brick;
	Effect* effect;
	Background* background;
	Islands* islands;
	Wall* wall;
	Ladder* ladder;
	Greenery* greenery;
	
	// enemy
	Mine_factory* mine_factory;
	
public:

	Halloween();
    ~Halloween();
    void free();
	void reset();
	
    void load( int screen_w, int screen_h );
    void handle( sf::Event &event );
    void draw( sf::RenderWindow* &window );
	
	bool positioning( int type, int size, int flatness, int hover, int pug, int mine );
	string getInfo();
	
	bool nextState();
	bool backToLevel();
	void mechanics();
};