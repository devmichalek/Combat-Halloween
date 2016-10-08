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
	
	std::string ID;	// Universal ID
	
	int volume;
	std::string path;
    Mix_Music* music;

public:

    Music();
    ~Music();
    void free();	// Delete objects
	void setID( std::string name );	// Easier to find bugs
	
	#ifdef _WIN32
	void setColor( int i );
	#endif
	
    void load( std::string path, int volume = 0 );
	void reload();
    void play();
	
    void pause();
    void halt();
	
	void fadein( int i = 1, int max = 128 );
	void fadeout( int i = 1, int min = 0 );
	
	void setVolume( int volume );
	int getVolume();

    inline Mix_Music* get();
	std::ostream& operator <<( std::ostream& s );	// Print ID, path and volume
};
