#pragma once
#include <memory>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "audio.h"

namespace cmm
{
	class Sound : public SoundData
	{
	protected:
		std::unique_ptr<sf::Sound> sound;
		std::unique_ptr<sf::SoundBuffer> buffer;

	public:
		void stop();
		void play();
		const bool isPlaying() const;
		void pause();
		std::string load(const char* path);
		void setVolume(const float &newVolume);
		float getVolume() const;
		const bool& isPlayable() const;

		static void setGlobalPlayable(bool newPlayable = true);
		static bool getGlobalPlayable();
		static void setGlobalVolume(const float &newVolume);
		static float getGlobalVolume();
	};
}