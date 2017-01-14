#pragma once

#include <SFML/Graphics/Color.hpp>

class Sound
{
	bool chunk_play;
	bool music_play;
	sf::Uint8 chunk_volume;
	sf::Uint8 music_volume;
	
public:
	
	Sound();
	~Sound();
	
	void setChunkVolume( sf::Uint8 volume );
	void setChunkPlay( bool play );
	
	sf::Uint8 getChunkVolume();
	bool getChunkPlay();
	
	void setMusicVolume( sf::Uint8 volume );
	void setMusicPlay( bool play );
	
	sf::Uint8 getMusicVolume();
	bool getMusicPlay();
};