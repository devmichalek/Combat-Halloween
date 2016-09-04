#pragma once

#include "core.h"
#include "loading.h"
#include "link_button.h"
#include "menu_play_button.h"
#include "menu_title.h"
#include "menu_music_button.h"
#include "menu_log.h"
#include "menu_exit_log.h"
#include "music.h"

class Engine
{
    // Objects to load
    Core* core;
	
	// Loading state
	Loading* loading;
	
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

public:

    Engine();
    ~Engine();

    void free();
    void load();

    void events();
    void states();

    void loop();
};
