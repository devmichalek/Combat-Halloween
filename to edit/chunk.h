/**
    chunk.h
    Purpose: class Chunk to load and play wav files based on SDL_mixer

    @author Adrian Michalek
    @version 2016.09.07
	@email adrmic98@gmail.com
*/


#pragma once
#include <SDL2/SDL_mixer.h>		// Mix_Chunk, Mix_FreeChunk, Mix_GetError, Mix_VolumeChunk
#include <iostream>				// string, cerr, <<

class Chunk
{

protected:	

	Uint8 volume;
	std::string path;
    Mix_Chunk* chunk;

public:

    Chunk();
    ~Chunk();
	void free();	// Delete objects

    void load( std::string path, int volume = 0 );
    void play();

    inline Mix_Chunk* get();
    void setVolume( int volume );
	
	std::ostream& operator <<( std::ostream& s );	// Print path and volume
};