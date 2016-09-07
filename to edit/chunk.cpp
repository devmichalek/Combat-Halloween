/**
    chunk.cpp
    Purpose: class Chunk for wav files based on SDL_mixer

    @author Adrian Michalek
    @version 2016.09.07
	@email adrmic98@gmail.com
*/


#include "chunk.h"
#include <stdio.h>	// printf 

Chunk::Chunk()
{
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


void Chunk::load( std::string path, int volume )
{
    free();
	
	try
	{
		chunk = Mix_LoadWAV( path.c_str() );
		this->path = path;
		
		if( chunk == NULL )
			throw "\n\x1B[91mNot found\x1B[0m chunk " + path + "  Error " + Mix_GetError() + "\n";
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
			throw "\nVolume \x1B[91mneed to be between\x1B[0m 0 and 128\n";
	}
	catch( const char* msg )
	{
		std::cerr << msg << std::endl;
	}
}

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
	return s << "Chunk name: " << path << " volume: " << volume;
}
