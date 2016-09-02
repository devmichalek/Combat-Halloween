#pragma once

#include "core.h"
#include "link_button.h"
#include "menu_play_button.h"

class Engine
{
    // Objects to load
    Core* core;
	
	//Menu
	Link_button* git_button;
	Link_button* google_button;
	Link_button* twitter_button;
	Link_button* facebook_button;
	MySprite* menu_background;
	Menu_play_button* menu_play_button;

public:

    Engine();
    ~Engine();

    void free();
    bool load();

    void events();
    void states();

    void loop();
};
