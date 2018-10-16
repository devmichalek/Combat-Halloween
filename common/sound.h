#pragma once
#include <memory>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "audio.h"

namespace cmm
{
	class Sound : public SoundData
	{
		struct BufferMap
		{
			std::vector<std::string> paths;
			std::vector<sf::SoundBuffer*> buffers;

			BufferMap();
			~BufferMap();
			sf::SoundBuffer* get(std::string &path);
		};

		inline static BufferMap buffer_map;
	protected:
		std::unique_ptr<sf::Sound> sound;

	public:
		void stop();
		void play();
		const bool isPlaying() const;
		void pause();
		std::string load(std::string path);
		void setVolume(const float &newVolume);
		float getVolume() const;
		const bool& isPlayable() const;

		static void setGlobalPlayable(bool newPlayable = true);
		static bool getGlobalPlayable();
		static void setGlobalVolume(const float &newVolume);
		static float getGlobalVolume();
	};
}