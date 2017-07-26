#pragma once

#include "core.h"
#include "initialization/loading.h"
#include "initialization/initialization.h"
#include "initialization/login.h"
#include "menu/menu.h"

class Engine {
	
	enum {
		LOADING = 0,
		INIT,
		LOGIN,
		MENU,
		PLAY
	};
	
	Core* core;
	Loading* loading;
	Initialization* initialization;
	Login* login;
	Menu* menu;
	
public:
	Engine();
    ~Engine();

    void free();
    void load();

    void events();
    void states();

    void loop();
};