#include "sound.h"
#include <stdio.h>

bool Sound::chunk_play = false;
bool Sound::music_play = false;
sf::Uint8 Sound::chunk_volume = 0;
sf::Uint8 Sound::music_volume = 0;

Sound::Sound()
{
	// empty.
}

Sound::~Sound()
{
	free();
}

void Sound::free()
{
	// empty.
}
	

void Sound::setChunkVolume( sf::Uint8 volume )
{
	this->chunk_volume = volume;
}

void Sound::setChunkPlay( bool play )
{
	this->chunk_play = play;
}
	
sf::Uint8 Sound::getChunkVolume()
{
	return chunk_volume;
}

bool Sound::getChunkPlay()
{
	return chunk_play;
}



void Sound::setMusicVolume( sf::Uint8 volume )
{
	this->music_volume = volume;
}

void Sound::setMusicPlay( bool play )
{
	this->music_play = play;
}

sf::Uint8 Sound::getMusicVolume()
{
	return music_volume;
}

bool Sound::getMusicPlay()
{
	return music_play;
}