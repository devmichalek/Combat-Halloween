#pragma once

#include "core.h"
#include "00_loading/loading.h"
#include "01_intro/intro.h"
#include "02_menu/menu.h"
#include "03_level/level.h"


#include "04_platform/00_halloween/halloween.h"
#include "04_platform/01_forest/forest.h"
#include "04_platform/02_winter/winter.h"
#include "04_platform/03_desert/desert.h"


#include "05_loading_world/loading_world.h"
#include "06_panel/panel_menu.h"

class Engine
{
	enum
	{
		INTRO = -1,
		MENU,
		LEVEL,
		GEARS,
		HALLOWEEN,
		FOREST,
		WINTER,
		DESERT,
		PANEL
	};
	
    Core* core;
	Loading* loading;
	Intro* intro;
	Menu* menu;
	Level* level;
	Loading_world* gears;
	
	Halloween* halloween;
	Forest* forest;
	Winter* winter;
	Desert* desert;
	
	Panel_menu* panel;

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
