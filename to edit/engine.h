#pragma once

#include "core.h"
#include "loading/loading.h"
#include "intro/intro.h"
#include "menu/menu.h"
#include "play/game_timer.h"

class Engine
{
    Core* core;
	Loading* loading;
	Intro* intro;
	Menu* menu;
	
	//play
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
