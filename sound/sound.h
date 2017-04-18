/**
    sound.h
    Purpose: class Sound contains static members, uses as global switch with states.

    @author Adrian Michalek
    @version 2016.09.10
	@email adrmic98@gmail.com
*/

#pragma once

#include <SFML/Graphics/Color.hpp>
#include <stdbool.h>

class Sound
{
	static bool chunk_play;
	static bool music_play;
	static sf::Uint8 chunk_volume;
	static sf::Uint8 music_volume;
	
public:
	
	Sound();
	~Sound();
	void free();
	
	void setChunkVolume( sf::Uint8 volume );
	void setChunkPlay( bool play );
	
	sf::Uint8 getChunkVolume();
	bool getChunkPlay();
	
	void setMusicVolume( sf::Uint8 volume );
	void setMusicPlay( bool play );
	
	sf::Uint8 getMusicVolume();
	bool getMusicPlay();
};