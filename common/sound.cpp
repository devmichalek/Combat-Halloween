#include "sound.h"

bool cmm::Sound::playable = false;

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

void cmm::Sound::setVolume(float volume)
{
	sound->setVolume(static_cast<float> (volume));
}

float cmm::Sound::getVolume() const
{
	return sound->getVolume();
}

void cmm::Sound::setPlayable(bool newPlayable)
{
	playable = newPlayable;
}

const bool& cmm::Sound::isPlayable() const
{
	return playable;
}