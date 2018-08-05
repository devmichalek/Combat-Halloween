#include "music.h"

bool cmm::Music::playable = true;
float cmm::Music::volume = 60.0;

void cmm::Music::stop()
{
	music->stop();
}

void cmm::Music::play()
{
	if (playable && !isPlaying())
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

void cmm::Music::load(const char* path)
{
	music = std::make_unique<sf::Music>();
	if(music->openFromFile(path))
	{
		music->setLoop(true);
	}
}

void cmm::Music::setVolume(float newVolume)
{
	music->setVolume(newVolume);
}

float cmm::Music::getVolume() const
{
	return music->getVolume();
}

void cmm::Music::fadein(float v, int max)
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

void cmm::Music::fadeout(float v, int min)
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
	return playable;
}

void cmm::Music::setGlobalPlayable(bool newPlayable)
{
	playable = newPlayable;
}

bool cmm::Music::getGlobalPlayable()
{
	return playable;
}

void cmm::Music::setGlobalVolume(float newVolume)
{
	volume = newVolume;
}

float cmm::Music::getGlobalVolume()
{
	return volume;
}