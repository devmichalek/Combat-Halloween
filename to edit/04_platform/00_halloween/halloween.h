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
#include "04_platform/panel/scores/scores.h"
#include "04_platform/panel/hp_dot/hp_dots.h"
#include "04_platform/panel/score_dot/score_dots.h"

// World stuff
#include "04_platform/world/brick/brick.h"
#include "04_platform/world/background/effect.h"
#include "04_platform/world/background/background.h"
#include "04_platform/world/islands/islands.h"
#include "04_platform/world/wall/wall.h"
#include "04_platform/world/ladder/ladder.h"
#include "04_platform/world/greenery/greenery.h"
#include "04_platform/world/weather/rain/rain.h"
#include "04_platform/world/boulder/boulders.h"
#include "04_platform/world/door/door.h"

// Enemy
#include "04_platform/enemy/mine/mine_factory.h"
#include "04_platform/enemy/factory/factory.h"
#include "04_platform/enemy/zombie/zombie.h"
#include "04_platform/enemy/vampire/vampire.h"
#include "04_platform/enemy/checkActivity/lightning/lightning.h"
#include "04_platform/enemy/flying/fly_factory.h"

class Halloween
{
	int state;
	string info;
	sf::Uint8 fade;
	
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
	Scores* scores;
	Hp_dots* hp_dots;
	Score_dots* score_dots;
	
	// world
	Brick* brick;
	Effect* effect;
	Background* background;
	Islands* islands;
	Wall* wall;
	Ladder* ladder;
	Greenery* greenery;
	Rain* rain;
	Boulder* boulder;
	Door* door;
	
	// enemy
	Mine_factory* mine_factory;
	Factory <Vampire> vampire_factory;
	Factory <Zombie> zombie_factory;
	Lightning* lightning;
	Fly_factory* fly_factory;
	
public:

	Halloween();
    ~Halloween();
    void free();
	void reset();
	
    void load( int screen_w, int screen_h, unsigned FPS );
    void handle( sf::Event &event );
    void draw( sf::RenderWindow* &window );
	
	bool positioning( int type, int size, int flatness, int difficulty );
	string getInfo();
	
	bool defeatState();
	bool winState();
	bool backToLevel();
	void mechanics();
	
	void setSound();
	void reloadMusic();
};