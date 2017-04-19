#pragma once

#include "core.h"
#include "timer.h"
#include "initialization/loading.h"
#include "initialization/initialization.h"
#include "menu/menu.h"
#include "level/level.h"


#include "platform/halloween/halloween.h"
#include "platform/forest/forest.h"
#include "platform/winter/winter.h"
#include "platform/desert/desert.h"
#include "platform/future/future.h"


#include "panel/loading_world.h"
#include "panel/panel_menu.h"

class Engine
{
	enum
	{
		INIT = -1,
		MENU,
		LEVEL,
		GEARS,
		HALLOWEEN,
		FOREST,
		WINTER,
		DESERT,
		FUTURE,
		PANEL
	};
	
    Core* core;
	Timer* timer;
	Loading* loading;
	Initialization* initialization;
	Menu* menu;
	Level* level;
	Loading_world* gears;
	
	Halloween* halloween;
	Forest* forest;
	Winter* winter;
	Desert* desert;
	Future* future;
	
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
	
	template <typename world>
	void setPanel( world w );
};
