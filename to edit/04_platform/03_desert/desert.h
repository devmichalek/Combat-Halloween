#pragma once

// Sound
#include "sound/sound.h"
#include "sound/music.h"

// Hero stuff
#include "04_platform/ninja/ninja.h"
#include "04_platform/ninja/kunai/kunai.h"
#include "04_platform/ninja/scope/scope.h"

// Panel stuff
#include "04_platform/panel/heart/heart.h"
#include "04_platform/panel/money/money.h"
#include "04_platform/enemy/coins/coins.h"
#include "04_platform/panel/skill/skills.h"
#include "04_platform/panel/action/showdamage.h"
#include "04_platform/panel/action/showheal.h"

// World stuff
#include "04_platform/world/brick/brick.h"
#include "04_platform/world/background/effect.h"
#include "04_platform/world/background/background.h"
#include "04_platform/world/islands/islands.h"
#include "04_platform/world/wall/wall.h"
#include "04_platform/world/ladder/ladder.h"
#include "04_platform/world/greenery/greenery.h"
#include "04_platform/world/background/day.h"
#include "04_platform/world/weather/wind/wind.h"
#include "04_platform/world/boulder/boulder.h"


// Enemy
#include "04_platform/enemy/mine/mine_factory.h"
#include "04_platform/enemy/factory/factory.h"
#include "04_platform/enemy/skeleton/skeleton.h"
#include "04_platform/enemy/snakes/snakes_factory.h"
#include "04_platform/enemy/checkActivity/fireball/fireball.h"

class Desert
{
	int state;
	string info;
	
	int FPS;
	int width;
	int screen_w;
	int screen_h;
	
	// sound
	Sound sound;
	Music* music;
	
	// hero
	Hero* hero;
	Kunai* kunai;
	Scope* scope;
	
	// panel
	Heart* heart;
	Money* money;
	Coins* coins;
	Skills* skills;
	Showdamage* showdamage;
	Showheal* showheal;
	
	// world
	Brick* brick;
	Effect* effect;
	Background* background;
	Islands* islands;
	Wall* wall;
	Ladder* ladder;
	Greenery* greenery;
	Day* day;
	Wind* wind;
	Boulder* boulder;
	
	// enemy
	Mine_factory* mine_factory;
	Factory <Skeleton> skeleton_factory;
	Snakes_factory* snakes_factory;
	Fireball* fireball;
	
	
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
	
	void setSound();
	void reloadMusic();
};