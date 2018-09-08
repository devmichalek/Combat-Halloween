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

const bool cmm::Sound::isPlaying() const
{
	return sound->getStatus() == sf::SoundSource::Status::Playing;
}

void cmm::Sound::pause()
{
	sound->pause();
}

std::string cmm::Sound::load(const char* path)
{
	buffer = std::make_unique<sf::SoundBuffer>();
	if (buffer->loadFromFile(path))
	{
		sound = std::make_unique<sf::Sound>();
		sound->setBuffer(*buffer.get());
		return "Success: Sound \"" + std::string(path) + "\" loaded correctly.";
	}

	return "Error: Cannot create sound buffer from\"" + std::string(path) + "\".";
}

void cmm::Sound::setVolume(const float &newVolume)
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

void cmm::Sound::setGlobalVolume(const float &newVolume)
{
	volume = newVolume;
}

float cmm::Sound::getGlobalVolume()
{
	return volume;
}