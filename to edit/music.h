/**
    music.h
    Purpose: class Music to load and play mp3 files based on SDL_mixer

    @author Adrian Michalek
    @version 2016.09.06
	@email adrmic98@gmail.com
*/


#pragma once
#include <SDL2/SDL_mixer.h>
#include <iostream>

class Music
{
	
protected:
	
	Uint8 volume;
	std::string path;
    Mix_Music* music;

public:

    Music();
    ~Music();
    void free();	// Delete objects
	
    void load( std::string path, int volume = 0 );
    void play();
	
    void pause();
    void halt();
	
	void fadein( int i = 1, int max = 128 );
	void fadeout( int i = 1, int min = 0 );

    inline Mix_Music* get();
	std::ostream& operator <<( std::ostream& s );	// Print path and volume
};
