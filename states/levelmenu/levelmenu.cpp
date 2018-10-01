#include "levelmenu.h"
#include "loading.h"

LevelMenu::LevelMenu()
{
	free();
}

LevelMenu::~LevelMenu()
{
	free();
}

void LevelMenu::free()
{
	prev = false;
	next = false;
	exit = false;
	loaded = false;

	homebutton.free();
	updatebutton.free();
	playbutton.free();
	soundbutton.free();
	musicbutton.free();
	sound_volumebutton.free();
	music_volumebutton.free();
	information.free();
	chat.free();
	pausesystem.free();
}

void LevelMenu::set()
{
	if (!loaded)
	{
		loaded = true;

		// Set threads.
		// knightspecs.setThread();

		// Sound.
		bool soundPlayable = cmm::Sound::getGlobalPlayable();
		float soundVolume = cmm::Sound::getGlobalVolume();

		homebutton.setVolume				(soundVolume);
		updatebutton.setVolume				(soundVolume);
		playbutton.setVolume				(soundVolume);
		soundbutton.setVolume				(soundVolume);
		musicbutton.setVolume				(soundVolume);
		sound_volumebutton.setVolume		(soundVolume);
		sound_volumebutton.setGlobalVolume	(soundVolume);
		music_volumebutton.setVolume		(soundVolume);
		information.setVolume				(soundVolume);
		pausesystem.setVolume				(soundVolume);
		soundbutton.setActive				(soundPlayable);

		// Music.
		bool musicPlayable = cmm::Music::getGlobalPlayable();
		float musicVolume = cmm::Music::getGlobalVolume();

		music.setVolume						(musicVolume);
		music_volumebutton.setGlobalVolume	(musicVolume);
		musicbutton.setActive				(musicPlayable);
		musicbutton.isActive() ? music.play() : music.pause();
	}
}

bool LevelMenu::isReady() const
{
	return information.getBackgroundAlpha() == 0;
}

void LevelMenu::reset()
{
	prev = false;
	next = false;
	exit = false;
	loaded = false;
	
	homebutton.setActive(false);
	playbutton.setActive(false);
	music.stop();
	chat.reset();
	chat.setStyleBlackish();
}



void LevelMenu::load(const float &screen_w, const float &screen_h)
{
	free();

	float scale_x = screen_w / 2560;
	float scale_y = screen_h / 1440;

	// Circle buttons.
	homebutton.load		("images/buttons/home.png");
	updatebutton.load	("images/buttons/update.png");
	playbutton.load		("images/buttons/play.png");
	soundbutton.load	("images/buttons/sound.png");
	musicbutton.load	("images/buttons/music.png");
	if (Loading::isError())	return;
	homebutton.setScale		(scale_x, scale_y);
	updatebutton.setScale	(scale_x, scale_y);
	playbutton.setScale		(scale_x, scale_y);
	soundbutton.setScale	(scale_x, scale_y);
	musicbutton.setScale	(scale_x, scale_y);
	homebutton.setPosition		(screen_w / 256, screen_h / 144);
	updatebutton.setPosition	(homebutton.getRight() + screen_w / 256, screen_h / 144);
	playbutton.setPosition		(screen_w - screen_w / 256 - playbutton.getWidth(), screen_h / 144);
	soundbutton.setPosition		(screen_w - screen_w / 256 - soundbutton.getWidth(), screen_h - screen_h / 144 - soundbutton.getHeight());
	musicbutton.setPosition		(soundbutton.getLeft() - screen_w / 256 - musicbutton.getWidth(), soundbutton.getTop());


	// Set volume buttons.
	sound_volumebutton.load(screen_w, screen_h);
	music_volumebutton.load(screen_w, screen_h);
	if (Loading::isError())	return;
	sound_volumebutton.setPosition(soundbutton.getLeft(), soundbutton.getRight(), soundbutton.getBot());
	music_volumebutton.setPosition(musicbutton.getLeft(), musicbutton.getRight(), musicbutton.getBot());

	information.load(screen_w, screen_h);

	chat.load(screen_w, screen_h);
	chat.setStyleBlackish();
	
	pausesystem.load(screen_w, screen_h);
	music.load("music/levelmenu.ogg");
	if (Loading::isError())	return;
}

void LevelMenu::handle(const sf::Event &event)
{
	if (!isState())
	{
		if (!pausesystem.isActive() && pausesystem.getAlpha() == 0)
		{
			chat.handle(event);

			if (!chat.isActive())
			{
				homebutton.handle(event);
				updatebutton.handle(event);
				playbutton.handle(event);

				if (!sound_volumebutton.handle(event))	soundbutton.handle(event);
				if (!music_volumebutton.handle(event))	musicbutton.handle(event);

				information.handle(event);
			}
		}

		if (!chat.isActive())
		{
			pausesystem.handle(event);
		}
	}
}

void LevelMenu::draw(sf::RenderWindow* &window)
{
	information.draw			(window);
	homebutton.draw				(window);
	updatebutton.draw			(window);
	playbutton.draw				(window);
	soundbutton.draw			(window);
	musicbutton.draw			(window);
	sound_volumebutton.draw		(window);
	music_volumebutton.draw		(window);
	chat.draw					(window);
	pausesystem.draw			(window);
}

void LevelMenu::mechanics(const double &elapsedTime)
{
	set();

	fades(elapsedTime);

	// Mechanics.
	if (!pausesystem.isActive() && !isState())
	{
		chat.mechanics(elapsedTime);
		if (chat.isCommand())
		{
			if (chat.compCommand("@close") || chat.compCommand("@exit"))
			{
				chat.isActive() = false;
				exit = true;
			}
			else if (chat.compCommand("@menu") || chat.compCommand("@back") || chat.compCommand("@home"))
			{
				homebutton.setActive(true);
			}

			// Same as someone clicked play.
			/*else if (chat.findCommand("@play") || chat.findCommand("@start"))
			{
				if (worldtable.isChosen())
				{
					playbutton.setActive(true);
				}
			}*/

			// Reload data.
			/*else if (chat.findCommand("@reload"))
			{
				if (worldtable.abletoreload())
				{

					worldtable.setThread();
				}
			}*/
			// Chat changed keys settings so we reload texts
			else if (chat.isNewCoxing())
			{
				if (chat.checkCoxing())
				{
					// ...?
				}
			}

			// Update data.
			else if (chat.compCommand("@reload"))
			{
				updatebutton.setChanged(true);
			}

			// Turn on/off all sounds.
			else if (chat.compCommand("@sound"))
			{
				soundbutton.setChanged(true);
				soundbutton.setActive(!soundbutton.isActive());
			}

			// Turn on/off music.
			else if (chat.compCommand("@music"))
			{
				musicbutton.setChanged(true);
				musicbutton.setActive(!musicbutton.isActive());
			}

			// Editor.
			else if (chat.compCommand("@editor"))
			{
				prev = true;
				chat.isActive() = false;
			}

			// Volume
			else if (chat.isNewMusicVolume())
			{
				float value = chat.getNewVolume();
				if (value != -1)
					music_volumebutton.setChanged(value);
			}
			else if (chat.isNewSoundVolume())
			{
				float value = chat.getNewVolume();
				if (value != -1)
					sound_volumebutton.setChanged(value);
			}

			// Else
			else
				chat.setError();
		}

		// Back to menu.
		if (homebutton.isActive())
		{
			chat.isActive() = false;
			prev = true;
		}

		// Start game.
		if (playbutton.isActive())
		{
			chat.isActive() = false;
			next = true;
		}

		sound_volumebutton.mechanics(elapsedTime);
		music_volumebutton.mechanics(elapsedTime);

		// Turn on/off all sounds.
		if (soundbutton.hasChanged())
		{
			cmm::Sound::setGlobalPlayable(soundbutton.isActive());
		}

		// Volume of sounds is changed.
		if (sound_volumebutton.hasChanged())
		{
			float value = sound_volumebutton.getGlobalVolume();
			cmm::Sound::setGlobalVolume(value);
			homebutton.setVolume(value);
			updatebutton.setVolume(value);
			playbutton.setVolume(value);
			soundbutton.setVolume(value);
			musicbutton.setVolume(value);
			sound_volumebutton.setVolume(value);
			music_volumebutton.setVolume(value);
			information.setVolume(value);
			pausesystem.setVolume(value);
		}

		// Turn on/off music.
		if (musicbutton.hasChanged())
		{
			cmm::Music::setGlobalPlayable(musicbutton.isActive());
			musicbutton.isActive() ? music.play() : music.pause();
		}

		// Volume of music is changed.
		if (music_volumebutton.hasChanged())
		{
			float value = music_volumebutton.getGlobalVolume();
			cmm::Music::setGlobalVolume(value);
			music.setVolume(value);
		}
	}
}

void LevelMenu::setState(int &state)
{
	if (isPrev() && isNext())
	{
		reset();
		state = cmm::STATES::EDITOR;
	}
	else if (isPrev())
	{
		reset();
		state = cmm::STATES::MENU;
	}
	else if (isNext())
	{
		reset();
		state = cmm::STATES::PLATFORM;
	}
	else if (isExit())
	{
		reset();
		cmm::StaticCore::open = false;
	}
}

void LevelMenu::fades(const double &elapsedTime)
{
	if (pausesystem.isActive())
	{
		const float value = (float)elapsedTime * 0xFF * 2;
		const int min = 0xFF * 3 / 4;
		fadeout(value, min);
		pausesystem.fadein(value * 3, min);
		music.fadeout((float)elapsedTime * 100, (int)(music_volumebutton.getGlobalVolume() * 0.2));
	}
	else if (isState())
	{
		const int min = 0;
		fadeout((float)elapsedTime * 0xFF, min);
		music.fadeout((float)elapsedTime * 100, min);
	}
	else
	{
		const float value = (float)elapsedTime * 0xFF * 2;
		const int max = 0xFF, min = 0;
		fadein(value, max);
		pausesystem.fadeout(value, min);
		music.fadein((float)elapsedTime * 100, (int)music_volumebutton.getGlobalVolume());
	}
}

void LevelMenu::fadein(const float &value, const int &max)
{
	homebutton.fadein			(value, max);
	updatebutton.fadein			(value, max);
	playbutton.fadein			(value, max);
	soundbutton.fadein			(value, max);
	musicbutton.fadein			(value, max);
	sound_volumebutton.fadein	(value, max);
	music_volumebutton.fadein	(value, max);
	information.fadein			(value, max);
}

void LevelMenu::fadeout(const float &value, const int &min)
{
	homebutton.fadeout			(value, min);
	updatebutton.fadeout		(value, min);
	playbutton.fadeout			(value, min);
	soundbutton.fadeout			(value, min);
	musicbutton.fadeout			(value, min);
	sound_volumebutton.fadeout	(value, min);
	music_volumebutton.fadeout	(value, min);
	information.fadeout			(value, min);
	chat.fadeout				(value, min);
}