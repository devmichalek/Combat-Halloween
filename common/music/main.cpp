#include "music.h"

int main(int argc, char** argv)
{
	cmm::Music music;
	music.load("music/menu.ogg");
	cmm::Music::setGlobalPlayable();
	music.setVolume(100);
	music.play();

	bool state = true;
	float v = static_cast<float>(0.0001);

	while (music.isPlaying())
	{
		if (music.getVolume() == 100)		state = true;
		else if (music.getVolume() == 0)	state = false;

		int v = 1;
		float min = 0.0f, max = 255.0f;

		state ? music.fadeout(v, min) : music.fadein(v, max);
	}

	return 0;
}