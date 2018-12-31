#include "sound.h"
#include "music.h"
#include "converter.h"
#include <iostream>

int main(int argc, char** argv)
{
	cmm::Audio audio;
	audio.loadAudio();

	cmm::Sound sound;
	sound.load("sounds/click.wav");
	cmm::Sound::setGlobalPlayable();
	sound.setVolume(100);
	sound.play();

	while (sound.isPlaying()) {}

	// Coontinue
	std::cout << "Press Enter to Continue..." + cmm::SNEWLINE;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), cmm::CNEWLINE);


	cmm::Music music;
	music.load("music/menu.ogg");
	cmm::Music::setGlobalPlayable();
	music.setVolume(100);
	music.play();

	bool state = true;

	while (music.isPlaying())
	{
		if (music.getVolume() == 100)		state = true;
		else if (music.getVolume() == 0)	state = false;

		float v = 1.0f;
		int min = 0, max = 255;

		state ? music.fadeout(v, min) : music.fadein(v, max);
	}

	return 0;
}
