#pragma once

#include <SDL2/SDL_mixer.h>

class Music
{
    Mix_Music* music;
	int volume;

public:

    Music();
    ~Music();

    void free();
    bool load( const char* path, int volume = 0 );

    void play();
    void pause();
    void halt();
	
	void fadein( int i = 1, int max = 128 );
	void fadeout( int i = 1, int min = 0 );

    Mix_Music* get();
};
