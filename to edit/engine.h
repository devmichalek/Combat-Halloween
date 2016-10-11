#pragma once

#include "core.h"
#include "templates/sprite.h"

class Engine
{
    Core* core;
	MySprite* leftSide;

public:

    Engine();
    ~Engine();

    void free();
    void load();

    void events();
    void states();

    void loop();
};
