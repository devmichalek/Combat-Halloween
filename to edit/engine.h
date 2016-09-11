#pragma once

#include "core.h"
#include "start/loading.h"
#include "start/intro.h"
#include "menu/link_button.h"
#include "menu/menu_play_button.h"
#include "menu/menu_title.h"
#include "menu/menu_music_button.h"
#include "menu/menu_log.h"
#include "menu/menu_exit_log.h"
#include "templates/music.h"
#include "play/game_timer.h"

class Engine
{
    // Objects to load
    Core* core;
	
	// Loading state
	Loading* loading;
	
	// Intro state
	Intro* intro;
	
	// Menu state
	Link_button* git_button;
	Link_button* google_button;
	Link_button* twitter_button;
	Link_button* facebook_button;
	MySprite* menu_background;
	Menu_play_button* menu_play_button;
	Menu_title* menu_title;
	Menu_music_button* menu_music_button;
	Menu_music_button* menu_chunk_button;
	Menu_log* author_log;
	Menu_log* game_log;
	Menu_log* settings_log;
	Menu_log* scores_log;
	Menu_exit_log* menu_exit;
	Music* menu_music;
	
	// Play state
	Game_timer* game_timer;

public:

    Engine();
    ~Engine();

    void free();
    void load();

    void events();
    void states();

    void loop();
};
