#include "core.h"
#include "sound.h"
#include <iostream>

int main(int argc, char** argv)
{
	cmm::Sound sound;
	sound.load("sounds/click.wav");
	cmm::Sound::setGlobalPlayable();
	sound.setVolume(100);
	sound.play();

	while (sound.isPlaying()) {}

	// Finish
	std::cout << "Press Enter to Continue...\n";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return 0;
}