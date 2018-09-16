#pragma once

namespace cmm
{
	class SoundData
	{
	protected:
		static bool sound_playable;
		static float sound_volume;
	};

	class MusicData
	{
	protected:
		static bool music_playable;
		static float music_volume;
	};

	class Audio : public SoundData, public MusicData
	{
	public:
		static const bool& isSoundPlayable();
		static const bool& isMusicPlayable();
		static const float& getSoundVolume();
		static const float& getMusicVolume();
		void resetAudio();
		void saveAudio();
		void loadAudio();
	};
}