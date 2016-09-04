#include "music.h"
#include <stdio.h>

Music::Music()
{
    music = NULL;
	volume = 0;
}

Music::~Music()
{
    free();
}


void Music::free()
{
    if( music != NULL )
    {
        Mix_FreeMusic( music );
        music = NULL;
    }
	volume = 0;
}

bool Music::load( const char* path, int volume )
{
    bool success = true;

    free();

    music = Mix_LoadMUS( path );
    if( music == NULL )
    {
        printf( "Not found music %s\n", path );
        printf( "Error %s\n", Mix_GetError() );
        success = false;
    }
    else if( volume != 0 )
    {
		this->volume = volume;
        Mix_VolumeMusic( volume );
    }

    return success;
}


void Music::play()
{
    if( Mix_PlayingMusic() == 0 )
    {
        Mix_PlayMusic( music, -1 );
    }
}

void Music::pause()
{
    if( Mix_PausedMusic() == 0 )
    {
        Mix_PauseMusic();
    }
	else if( Mix_PausedMusic() == 1 )
    {
        Mix_ResumeMusic();
    }
}

void Music::halt()
{
    Mix_HaltMusic();
}


void Music::fadein( int i, int max )
{
	if( volume < max )
	{
		volume += i;
		if( volume > max )
			volume = max;
		
		Mix_VolumeMusic( volume );
	}
}

void Music::fadeout( int i, int min )
{
	if( volume > min )
	{
		volume -= i;
		if( volume < min )
			volume = min;
		
		Mix_VolumeMusic( volume );
	}
}


Mix_Music* Music::get()
{
    return music;
}
