#pragma once
#include "core.h"
#include "initialization/loading.h"
#include "initialization/initialization.h"
#include "initialization/login.h"
#include "menu/menu.h"
#include "level/level.h"
#include "play/play.h"
#include "editor/editor.h"

class Engine {
	
	enum {
		LOADING = 0,
		INIT,
		LOGIN,
		MENU,
		LEVEL,
		PLAY,
		TABLE,
		EDITOR
	};
	
	Core* core;
	Loading* loading;
	Initialization* initialization;
	Login* login;
	Menu* menu;
	Level* level;
	Play* play;
	Editor* editor;
	
public:
	Engine();
    ~Engine();

    void free();
    void load();

    void events();
    void states();

    void loop();
};