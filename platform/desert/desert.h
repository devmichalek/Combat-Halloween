#pragma once


// Sound.
#include "sound/sound.h"
#include "sound/music.h"


// Hero.
#include "platform/ninja/base/ninja.h"
#include "platform/ninja/kunai/kunai.h"
#include "platform/ninja/scope/scope.h"


// Panel.
#include "platform/panel/skill/skills.h"
#include "platform/panel/heart/heart.h"
#include "platform/panel/scores/scores.h"
#include "platform/panel/money/money.h"
#include "platform/panel/pause/pause.h"
#include "platform/panel/sound_pad/sound_pad.h"
#include "platform/panel/time_box/time_box.h"


// Actions.
#include "platform/enemy/actions/hp_dots/hp_dots.h"
#include "platform/enemy/actions/coins/coins.h"
#include "platform/enemy/actions/show/showdamage.h"
#include "platform/enemy/actions/show/showheal.h"
#include "platform/enemy/actions/effect/effect.h"


// World,
#include "platform/world/background/background.h"
#include "platform/world/brick/brick.h"
#include "platform/world/islands/islands.h"
#include "platform/world/greenery/greenery.h"
#include "platform/world/ladder/ladder.h"
#include "platform/world/wall/wall.h"
#include "platform/world/boulder/boulders.h"
#include "platform/world/score_dots/score_dots.h"
#include "platform/world/exit/exit.h"
// in addition.
#include "platform/world/background/day.h"
#include "platform/world/weather/wind/wind.h"


// Enemy.
#include "platform/enemy/foes/checkActivity/fireball/fireball.h"
#include "platform/enemy/foes/mines/mine_factory.h"
#include "platform/enemy/foes/factory/factory.h"
#include "platform/enemy/foes/skeleton/skeleton.h"
#include "platform/enemy/foes/snakes/snakes_factory.h"
#include "platform/enemy/foes/flying/fly_factory.h"

class Desert
{
	int state;
	int type;
	string info;
	sf::Uint8 fade;
	int coruption;
	
	int FPS;
	int width;
	int screen_w;
	int screen_h;
	
	// Sound.
	Sound sound;
	Music* music;
	
	// Hero.
	Hero* hero;
	Kunai* kunai;
	Scope* scope;
	
	// Panel.
	Skills* skills;
	Heart* heart;
	Scores* scores;
	Money* money;
	Pause* pause;
	Sound_pad* sound_pad;
	Time_box* time_box;
	
	// Actions.
	Hp_dots* hp_dots;
	Coins* coins;
	Showdamage* showdamage;
	Showheal* showheal;
	Effect* effect;
	
	// World,
	Background* background;
	Brick* brick;
	Islands* islands;
	Greenery* greenery;
	Ladder* ladder;
	Wall* wall;
	Boulder* boulder;
	Score_dots* score_dots;
	Exit* exit;
	// in addition.
	Day* day;
	Wind* wind;
	
	
	// Enemy.
	Fireball* fireball;
	Mine_factory* mine_factory;
	Factory <Skeleton> skeleton_factory;
	Snakes_factory* snakes_factory;
	Fly_factory* fly_factory;
	
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
	
	bool defeatState();
	bool winState();
	int getScores();
	int getType();
	int getCoruption();
	string getTimePlayed();
	int getDeactivatedMines();
	int getEarnedMoney();
	
	bool backToLevel();
	void mechanics();
	
	void setSound();
	void reloadMusic();
};