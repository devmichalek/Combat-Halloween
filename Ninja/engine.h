#pragma once

#include "core.h"
#include "link_button.h"

class Engine
{
    // Objects to load
    Core* core;
	
	//Menu
	Link_button* git_button;
	Link_button* google_button;
	Link_button* twitter_button;
	Link_button* facebook_button;

public:

    Engine();
    ~Engine();

    void free();
    bool load();

    void events();
    void states();

    void loop();
};
