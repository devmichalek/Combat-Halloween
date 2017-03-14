#include "timer.h"

Timer::Timer( Uint32 fps )
{
    this->fps = 1000 / fps;
    startTicks = 0;
    pausedTicks = 0;

    paused = false;
    started = false;
}

void Timer::start()
{
    started = true;
    paused = false;

    startTicks = SDL_GetTicks();
    pausedTicks = 0;
}

void Timer::stop()
{
    started = false;
    paused = false;

    startTicks = 0;
    pausedTicks = 0;
}

void Timer::pause()
{
    if( started && !paused )
    {
        paused = true;
        pausedTicks = SDL_GetTicks() - startTicks;
        startTicks = 0;
    }
}

void Timer::unpause()
{
    if( started && paused )
    {
        paused = false;
        startTicks = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    }
}

Uint32 Timer::get_ticks()
{
    Uint32 time = 0;

    if( started )
    {
        if( paused )    time = pausedTicks;
        else            time = SDL_GetTicks() - startTicks;
    }

    return time;
}

void Timer::setFPS()
{
    Uint32 time = 0;

    if( started )
    {
        if( paused )    time = pausedTicks;
        else            time = SDL_GetTicks() - startTicks;
    }
	
	
    if( time < fps )
        SDL_Delay( fps - time );
	
	// if( time > 0 )
		// printf( "fps: %d\n", static_cast <int> (1000 /time) );
}

unsigned Timer::getFPS()
{
	// printf( "%d\n", 1000 /fps );
	return 1000 /fps;
}