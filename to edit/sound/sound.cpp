#include "sound.h"

Sound::Sound()
{
	chunk_play = false;
	music_play = false;
	chunk_volume = 0;
	music_volume = 0;
}

Sound::~Sound()
{
	free();
}

void Sound::free()
{
	chunk_play = false;
	music_play = false;
	chunk_volume = 0;
	music_volume = 0;
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
