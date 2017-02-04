#pragma once

#include "core.h"
#include "00_loading/loading.h"
#include "01_intro/intro.h"
#include "02_menu/menu.h"
#include "03_level/levelmenu.h"
#include "04_platform/wood/play_wood.h"
#include "04_platform/halloween/play_halloween.h"
#include "04_platform/desert/play_desert.h"
#include "04_platform/winter/play_winter.h"
#include "05_loading_world/loading_world.h"
#include "06_panel/panel_menu.h"

class Engine
{
    Core* core;
	Loading* loading;
	Intro* intro;
	Menu* menu;
	Level_menu* level_menu;
	Loading_world* loading_world;
	
	Play_wood* play_wood;
	Play_halloween* play_halloween;
	Play_desert* play_desert;
	Play_winter* play_winter;
	
	Panel_menu* panel_menu;

public:

    Engine();
    ~Engine();

    void free();
    void load();

    void events();
    void states();

    void loop();
	
	template <typename world>
	void load_world( world w );
};
