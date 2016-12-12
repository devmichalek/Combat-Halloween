#pragma once

#include "core.h"
#include "loading/loading.h"
#include "intro/intro.h"
#include "menu/menu.h"
#include "level/levelmenu.h"

#include "wood/play_wood.h"
#include "halloween/play_halloween.h"
#include "desert/play_desert.h"
#include "winter/play_winter.h"

class Engine
{
    Core* core;
	Loading* loading;
	Intro* intro;
	Menu* menu;
	Level_menu* level_menu;
	
	Play_wood* play_wood;
	Play_halloween* play_halloween;
	Play_desert* play_desert;
	Play_winter* play_winter;

public:

    Engine();
    ~Engine();

    void free();
    void load();

    void events();
    void states();

    void loop();
};
