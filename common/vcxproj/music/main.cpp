#include "music.h"

int main(int argc, char** argv)
{
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