#pragma once
#include <memory>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

namespace cmm
{
	class Sound
	{
		static bool playable;
	protected:
		std::unique_ptr<sf::Sound> sound;
		std::unique_ptr<sf::SoundBuffer> buffer;

	public:
		void stop();
		void play();
		bool isPlaying() const;
		void pause();
		void load(const char* path);
		void setVolume(float volume = 50);
		float getVolume() const;
		static void setPlayable(bool newPlayable = true);
		const bool& isPlayable() const;
	};
}