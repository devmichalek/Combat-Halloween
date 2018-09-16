#include "sound.h"

void cmm::Sound::stop()
{
	sound->stop();
}

void cmm::Sound::play()
{
	if (sound_playable && !isPlaying())
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
	return sound_playable;
}

void cmm::Sound::setGlobalPlayable(bool newPlayable)
{
	sound_playable = newPlayable;
}

bool cmm::Sound::getGlobalPlayable()
{
	return sound_playable;
}

void cmm::Sound::setGlobalVolume(const float &newVolume)
{
	sound_volume = newVolume;
}

float cmm::Sound::getGlobalVolume()
{
	return sound_volume;
}