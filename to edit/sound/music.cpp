/**
    music.cpp
    Purpose: class Music to load and play mp3 files based on SDL_mixer

    @author Adrian Michalek
    @version 2016.09.06
	@email adrmic98@gmail.com
*/


#include "music.h"
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

Music::Music()
{
	ID = "";
	
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

void Music::setID( std::string name )
{
	ID = name;
}


#ifdef __linux__
void Music::load( std::string path, int volume )
{
    free();
	
	try
	{
		music = Mix_LoadMUS( path.c_str() );
		this->path = path;
		
		if( music == NULL )
			throw "ID: " + ID + " \x1B[91mnot found\x1B[0m music " + path + "  Error " + Mix_GetError();
	}
	catch( std::string msg )
	{
		std::cerr << msg << std::endl;
	}
	
	
	try
	{
		Mix_VolumeMusic( volume );
		this->volume = volume;
		
		if( this->volume < 0 || this->volume > 128 )
			throw "ID: " + ID + " file: " + path + ": volume \x1B[91mneed to be between\x1B[0m 0 and 128";
	}
	catch( const char* msg )
	{
		std::cerr << msg << std::endl;
	}
}

void Music::reload()
{
	if( music != NULL )
    {
        Mix_FreeMusic( music );
        music = NULL;
    }
	
	try
	{
		music = Mix_LoadMUS( path.c_str() );
		
		if( music == NULL )
			throw "ID: " + ID + " \x1B[91mnot found\x1B[0m music " + path + "  Error " + Mix_GetError();
	}
	catch( std::string msg )
	{
		std::cerr << msg << std::endl;
	}
	
	
	try
	{
		Mix_VolumeMusic( volume );
		
		if( this->volume < 0 || this->volume > 128 )
			throw "ID: " + ID + " file: " + path + ": volume \x1B[91mneed to be between\x1B[0m 0 and 128";
	}
	catch( const char* msg )
	{
		std::cerr << msg << std::endl;
	}
}

#elif _WIN32
void Music::setColor( int i )
{
	HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( h, i );
}

void Music::load( std::string path, int volume )
{
    free();
	
	try
	{
		music = Mix_LoadMUS( path.c_str() );
		this->path = path;
		
		if( music == NULL )
		{
			throw "ID: " + ID + " ";
			setColor( 12 );
			throw "not found";
			setColor( 7 );
			throw " music " + path + "  Error " + Mix_GetError();
		}
	}
	catch( std::string msg )
	{
		std::cerr << msg << std::endl;
	}
	
	
	try
	{
		Mix_VolumeMusic( volume );
		this->volume = volume;
		
		if( this->volume < 0 || this->volume > 128 )
		{
			throw "ID: " + ID + " file: " + path + ": volume ";
			setColor( 12 );
			throw "need to be between";
			setColor( 7 );
			throw " 0 and 128";
		}
	}
	catch( const char* msg )
	{
		std::cerr << msg << std::endl;
	}
}
#endif


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
		//printf( "%d\n", volume );
		Mix_VolumeMusic( volume );
	}
}

void Music::setVolume( int volume )
{
	this->volume = volume;
	Mix_VolumeMusic( volume );
}

int Music::getVolume()
{
	return volume;
}


Mix_Music* Music::get()
{
    return music;
}

std::ostream& Music::operator <<( std::ostream& s )
{
	return s << "ID: " << ID << " music name: " << path << " volume: " << volume;
}
