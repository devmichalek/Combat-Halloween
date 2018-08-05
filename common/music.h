#pragma once
#include <memory>
#include <SFML/Audio/Music.hpp>

namespace cmm
{
	class Music
	{
		static bool playable;
		static float volume;
	protected:
		std::unique_ptr<sf::Music> music;

	public:
		void stop();
		void play();
		bool isPlaying() const;
		void pause();
		void load(const char* path);
		void setVolume(float newVolume = 50);
		float getVolume() const;
		void fadein(float v = 1, int max = 100);
		void fadeout(float v = 1, int min = 0);
		const bool& isPlayable() const;

		static void setGlobalPlayable(bool newPlayable = true);
		static bool getGlobalPlayable();
		static void setGlobalVolume(float newVolume);
		static float getGlobalVolume();
	};
}