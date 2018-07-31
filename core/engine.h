#pragma once
#include "core.h"
#include "loading.h"
#include "initialization.h"
#include "login.h"
#include "menu.h"
//#include "level/level.h"
//#include "play/play.h"
//#include "table/table.h"
//#include "editor/editor.h"

class Engine
{
	enum STATES
	{
		LOADING = 0,
		INIT,
		LOGIN,
		MENU,
		LEVEL,
		PLAY,
		TABLE
	};
	
	std::unique_ptr<Core> core;
	Loading* loading;
	Initialization* initialization;
	Login* login;
	Menu* menu;
	/*Level* level;
	Play* play;
	Table* table;*/
	
public:
	Engine();
	void loop();
private:
	void load();
	void events();
	void states();
};