#pragma once

#include "core.h"
#include "loading/loading.h"
#include "intro/intro.h"
#include "menu/menu.h"
#include "level/levelmenu.h"
#include "character/character_menu.h"
#include "wood/play_wood.h"

class Engine
{
    Core* core;
	Loading* loading;
	Intro* intro;
	Menu* menu;
	Level_menu* level_menu;
	Character_menu* character_menu;
	Play_wood* play_wood;

public:

    Engine();
    ~Engine();

    void free();
    void load();

    void events();
    void states();

    void loop();
};
