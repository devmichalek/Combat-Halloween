#pragma once

#include <SDL2/SDL.h>

class Timer
{
    float fps;
    Uint32 startTicks;
    Uint32 pausedTicks;
    bool paused;
    bool started;

public:

    Timer( float fps );
	void set( float fps );

    void start();
    void stop();
    void pause();
    void unpause();

    Uint32 get_ticks();
    void setFPS();
	float getFPS();
};