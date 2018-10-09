#pragma once
#include "core.h"
#include "loading.h"
#include "initialization.h"
#include "login.h"
#include "menu.h"
#include "levelmenu.h"
#include "platform.h"
//#include "table/table.h"
#include "editor.h"
#include "simulator.h"

class Engine
{	
	std::unique_ptr<cmm::Core> core;
	std::vector<cmm::State*> states;
	
public:
	Engine();
	~Engine();
	void loading_loop();
	void main_loop();
};