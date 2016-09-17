/**
    chunk.cpp
    Purpose: class Chunk for wav files based on SDL_mixer

    @author Adrian Michalek
    @version 2016.09.07
	@email adrmic98@gmail.com
*/


#include "chunk.h"

#ifdef _WIN32
#include <windows.h>
#endif

Chunk::Chunk()
{
	ID = "";
	
	volume = 0;
	path = "";
    chunk = NULL;
}

Chunk::~Chunk()
{
    free();
}

void Chunk::free()
{
	volume = 0;
	path = "";
	
    if( chunk != NULL )
    {
        Mix_FreeChunk( chunk );
        chunk = NULL;
    }
}

void Chunk::setID( std::string name )
{
	ID = name;
}


#ifdef __linux__
void Chunk::load( std::string path, int volume )
{
    free();
	
	try
	{
		chunk = Mix_LoadWAV( path.c_str() );
		this->path = path;
		
		if( chunk == NULL )
			throw "ID: " + ID + " \x1B[91mnot found\x1B[0m chunk " + path + "  Error " + Mix_GetError();
	}
	catch( std::string msg )
	{
		std::cerr << msg << std::endl;
	}
	
    
    try
	{
		Mix_VolumeChunk( chunk, volume );
		this->volume = volume;
		
		if( volume < 0 || volume > 128 )
			throw "ID: " + ID + " file: "+ path + ": volume \x1B[91mneed to be between\x1B[0m 0 and 128";
	}
	catch( std::string msg )
	{
		std::cerr << msg << std::endl;
	}
}

#elif _WIN32
void Chunk::setColor( int i )
{
	HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( h, i );
}

void Chunk::load( std::string path, int volume )
{
    free();
	
	try
	{
		chunk = Mix_LoadWAV( path.c_str() );
		this->path = path;
		
		if( chunk == NULL )
		{
			throw "ID: " + ID + " ";
			setColor( 12 );
			throw "not found";
			setColor( 7 );
			throw " chunk " + path + "  Error " + Mix_GetError();
		}
	}
	catch( std::string msg )
	{
		std::cerr << msg << std::endl;
	}
	
    
    try
	{
		Mix_VolumeChunk( chunk, volume );
		this->volume = volume;
		
		if( volume < 0 || volume > 128 )
		{
			throw "ID: " + ID + " file: "+ path + ": volume ";
			setColor( 12 );
			throw "need to be between";
			setColor( 7 );
			throw " 0 and 128";
		}
	}
	catch( std::string msg )
	{
		std::cerr << msg << std::endl;
	}
}
#endif


void Chunk::play()
{
    Mix_PlayChannel( -1, chunk, 0 );
}


Mix_Chunk* Chunk::get()
{
    return chunk;
}

void Chunk::setVolume( int volume )
{
    Mix_VolumeChunk( chunk, volume );
}


std::ostream& Chunk::operator <<( std::ostream& s )
{
	return s << "ID: " << ID << " chunk name: " << path << " volume: " << volume;
}
