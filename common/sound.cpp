#include "sound.h"

cmm::Sound::BufferMap::BufferMap()
{
	// ...
}

cmm::Sound::BufferMap::~BufferMap()
{
	if (!paths.empty())
		paths.clear();

	if (!buffers.empty())
	{
		for (auto &it : buffers)
		{
			delete it;
			it = nullptr;
		}
		buffers.clear();
	}
}

sf::SoundBuffer* cmm::Sound::BufferMap::get(std::string &path)
{
	auto it = std::find(paths.begin(), paths.end(), path);
	if (it != std::end(paths))
	{
		size_t pos = paths.size() - (paths.end() - it);
		return buffers[pos];
	}

	return nullptr;
}

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

std::string cmm::Sound::load(std::string path)
{
	sf::SoundBuffer* buffer = nullptr;
	sf::SoundBuffer* ptr = buffer_map.get(path);

	if (!ptr) // new one
		buffer = new sf::SoundBuffer();
	else
		buffer = ptr;

	if (!ptr && buffer->loadFromFile(path))
	{
		sound = std::make_unique<sf::Sound>();
		sound->setBuffer(*buffer);
		buffer_map.paths.push_back(path);
		buffer_map.buffers.push_back(buffer);
		return "Success: Sound \"" + std::string(path) + "\" loaded correctly.";
	}
	else if (ptr)
	{
		sound = std::make_unique<sf::Sound>();
		sound->setBuffer(*buffer);
		return "Success: Sound Buffer set correctly.";
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