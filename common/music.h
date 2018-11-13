#pragma once
#include <memory>
#include <SFML/Audio/Music.hpp>
#include "audio.h"

namespace cmm
{
	class Music : public MusicData
	{
	protected:
		std::unique_ptr<sf::Music> music;

	public:
		explicit Music();
		virtual ~Music() override;

		void stop();
		void play();
		bool isPlaying() const;
		void pause();
		std::string load(const char* path);
		void setVolume(const float &newVolume);
		float getVolume() const;
		void fadein(const float &v, const int &max);
		void fadeout(const float &v, const int &min);
		const bool& isPlayable() const;

		static void setGlobalPlayable(bool newPlayable = true);
		static bool getGlobalPlayable();
		static void setGlobalVolume(const float &newVolume);
		static float getGlobalVolume();
	};
}