#include "music.h"

void cmm::Music::stop()
{
	music->stop();
}

void cmm::Music::play()
{
	if (music_playable && !isPlaying())
	{
		music->play();
	}
}

bool cmm::Music::isPlaying() const
{
	return music->getStatus() == sf::SoundSource::Status::Playing;
}

void cmm::Music::pause()
{
	music->pause();
}

std::string cmm::Music::load(const char* path)
{
	music = std::make_unique<sf::Music>();
	if(music->openFromFile(path))
	{
		music->setLoop(true);
		return "Success: Music \"" + std::string(path) + "\" loaded correctly.";
	}

	return "Error: Cannot create music buffer from\"" + std::string(path) + "\".";
}

void cmm::Music::setVolume(const float &newVolume)
{
	music->setVolume(newVolume);
}

float cmm::Music::getVolume() const
{
	return music->getVolume();
}

void cmm::Music::fadein(const float &v, const int &max)
{
	if(music->getVolume() < max)
	{
		float newVolume = music->getVolume() + v;
		
		if(newVolume > max)
		{
			newVolume = static_cast<float>(max);
		}
		
		music->setVolume(newVolume);
	}
}

void cmm::Music::fadeout(const float &v, const int &min)
{
	if(music->getVolume() > min)
	{
		float newVolume = music->getVolume() - v;
		
		if(newVolume < min)
		{
			newVolume = static_cast<float>(min);
		}
		
		music->setVolume(newVolume);
	}
}

const bool& cmm::Music::isPlayable() const
{
	return music_playable;
}

void cmm::Music::setGlobalPlayable(bool newPlayable)
{
	music_playable = newPlayable;
}

bool cmm::Music::getGlobalPlayable()
{
	return music_playable;
}

void cmm::Music::setGlobalVolume(const float &newVolume)
{
	music_volume = newVolume;
}

float cmm::Music::getGlobalVolume()
{
	return music_volume;
}