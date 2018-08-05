#include "sound.h"

bool cmm::Sound::playable = true;
float cmm::Sound::volume = 50.0;

void cmm::Sound::stop()
{
	sound->stop();
}

void cmm::Sound::play()
{
	if (playable && !isPlaying())
	{
		sound->play();
	}
}

bool cmm::Sound::isPlaying() const
{
	return sound->getStatus() == sf::SoundSource::Status::Playing;
}

void cmm::Sound::pause()
{
	sound->pause();
}

void cmm::Sound::load(const char* path)
{
	buffer = std::make_unique<sf::SoundBuffer>();
	if (buffer->loadFromFile(path))
	{
		sound = std::make_unique<sf::Sound>();
		sound->setBuffer(*buffer.get());
	}
}

void cmm::Sound::setVolume(float newVolume)
{
	sound->setVolume(newVolume);
}

float cmm::Sound::getVolume() const
{
	return sound->getVolume();
}

const bool& cmm::Sound::isPlayable() const
{
	return playable;
}

void cmm::Sound::setGlobalPlayable(bool newPlayable)
{
	playable = newPlayable;
}

bool cmm::Sound::getGlobalPlayable()
{
	return playable;
}

void cmm::Sound::setGlobalVolume(float newVolume)
{
	volume = newVolume;
}

float cmm::Sound::getGlobalVolume()
{
	return volume;
}