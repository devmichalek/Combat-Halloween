#pragma once
#include "core.h"
#include "loading.h"
#include "initialization.h"
#include "login.h"
#include "menu.h"
#include "levelmenu.h"
//#include "play/play.h"
//#include "table/table.h"
//#include "editor/editor.h"

class Engine
{
	enum STATES
	{
		EMPTY = -2,
		LOADING = 0,
		INIT,
		LOGIN,
		MENU,
		LEVELMENU,
		PLATFORM,
		TABLE,
		EDITOR,
		DEFAULT
	};
	
	int initState, endState;
	std::unique_ptr<Core> core;
	Loading* loading;
	Initialization* initialization;
	Login* login;
	Menu* menu;
	LevelMenu* levelMenu;
	/*Play* play;
	Table* table;*/
	
public:
	Engine(int initState = STATES::INIT, int endState = STATES::DEFAULT);
	void loop();
private:
	void load();
	void events();
	void states();
};