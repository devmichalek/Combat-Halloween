#pragma once
#define _GLIBCXX_USE_CXX11_ABI 0
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <iostream>
using namespace std;

class Chunk
{
protected:
	string identity;
    sf::Sound* chunk;
	sf::SoundBuffer* buffer;
	bool playable; // able to play

public:

    Chunk();
    ~Chunk();
	void free();
	const sf::Sound* get() const;
	
	void setIdentity( string identity );
	const string& getIdentity() const;

    void load( string path );
	
	void stop();
    void play();
	void pause();
    void setVolume( float volume = 50 );
	void setPlayable( bool playable = true );
};