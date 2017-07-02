#pragma once
#define _GLIBCXX_USE_CXX11_ABI 0
#include <SFML/Audio/Music.hpp>
#include <iostream>
using namespace std;

class Music
{
	
protected:
	
	string identity;
    sf::Music* music;

public:

    Music();
    ~Music();
    void free();
	const sf::Music* get() const;
	
	void setIdentity( string identity );
	const string& getIdentity() const;
	
    void load( string path );
	
	void fadein( int v = 1, int max = 100 );
	void fadeout( int v = 1, int min = 0 );
	
	void stop();
    void play();
	void pause();
	void setVolume( float volume = 50 );
};
