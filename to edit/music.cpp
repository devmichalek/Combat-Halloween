/**
    music.cpp
    Purpose: class Music to load and play mp3 files based on SDL_mixer

    @author Adrian Michalek
    @version 2016.09.06
	@email adrmic98@gmail.com
*/


#include "music.h"
#include <stdio.h>	// printf

Music::Music()
{
	volume = 0;
	path = "";
    music = NULL;
}

Music::~Music()
{
    free();
}

void Music::free()
{
	volume = 0;
	path = "";
	
    if( music != NULL )
    {
        Mix_FreeMusic( music );
        music = NULL;
    }
}


void Music::load( std::string path, int volume )
{
    free();
	
	try
	{
		music = Mix_LoadMUS( path.c_str() );
		this->path = path;
		
		if( music == NULL )
			throw "\n\x1B[91mNot found\x1B[0m music " + path + "  Error " + Mix_GetError() + "\n";
	}
	catch( std::string msg )
	{
		std::cerr << msg << std::endl;
	}
	
	
	try
	{
		Mix_VolumeMusic( volume );
		this->volume = volume;
		
		if( volume < 0 || volume > 128 )
			throw "\nVolume \x1B[91mneed to be between\x1B[0m 0 and 128\n";
	}
	catch( const char* msg )
	{
		std::cerr << msg << std::endl;
	}
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

std::ostream& Music::operator <<( std::ostream& s )
{
	return s << "Chunk name: " << path << " volume: " << volume;
}
