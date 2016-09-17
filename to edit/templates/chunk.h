/**
    chunk.h
    Purpose: class Chunk to load and play wav files based on SDL_mixer

    @author Adrian Michalek
    @version 2016.09.07
	@email adrmic98@gmail.com
*/


#pragma once
#include <SDL2/SDL_mixer.h>
#include <iostream>

class Chunk
{

protected:	

	std::string ID;	// Universal

	Uint8 volume;
	std::string path;
    Mix_Chunk* chunk;

public:

    Chunk();
    ~Chunk();
	void free();	// Delete objects
	void setID( std::string name );	// To easier find bugs
	
	#ifdef _WIN32
	void setColor( int i );
	#endif

    void load( std::string path, int volume = 0 );
    void play();

    inline Mix_Chunk* get();
    void setVolume( int volume );
	
	std::ostream& operator <<( std::ostream& s );	// Print ID, path and volume
};