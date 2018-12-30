#include "menu.h"
#include "core.h"		// cmm::StaticCore::open
#include "loading.h"	// cmm::Music

Menu::Menu()
{
	free();
}

Menu::~Menu()
{
	free();
}

void Menu::free()
{
	prev = false;
	next = false;
	exit = false;
	loaded = false;

	knightspecs.free();
	github.free();
	scores.free();
	website.free();
	singleplayerbutton.free();
	multiplayerbutton.free();
	exitbutton.free();
	soundbutton.free();
	musicbutton.free();
	updatebutton.free();
	reloadbutton.free();
	settingsbutton.free();
	settings.free();
	sound_volumebutton.free();
	music_volumebutton.free();
	information.free();
	chat.free();
	pausesystem.free();
}

void Menu::set()
{
	if (!loaded)
	{
		loaded = true;

		// Set threads.
		knightspecs.setThread();
		information.setThread();

		// Sound.
		bool soundPlayable = cmm::Sound::getGlobalPlayable();
		float soundVolume = cmm::Sound::getGlobalVolume();

		// knightspecs.setVolume				(soundVolume);
		github.setVolume					(soundVolume);
		scores.setVolume					(soundVolume);
		website.setVolume					(soundVolume);
		singleplayerbutton.setVolume		(soundVolume);
		multiplayerbutton.setVolume			(soundVolume);
		exitbutton.setVolume				(soundVolume);
		soundbutton.setVolume				(soundVolume);
		musicbutton.setVolume				(soundVolume);
		updatebutton.setVolume				(soundVolume);
		reloadbutton.setVolume				(soundVolume);
		settingsbutton.setVolume			(soundVolume);
		settings.setVolume					(soundVolume);
		sound_volumebutton.setVolume		(soundVolume);
		sound_volumebutton.setGlobalVolume	(soundVolume);
		music_volumebutton.setVolume		(soundVolume);
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

bool Menu::isReady() const
{
	return information.getBackgroundAlpha() == 0;
}

void Menu::reset()
{
	prev = false;
	next = false;
	exit = false;
	loaded = false;
	
	singleplayerbutton.reset();
	settingsbutton.setActive(false);
	settings.reset();
	chat.reset();
	chat.setStyleBlackish();
	music.stop();
}



void Menu::load(const float &screen_w, const float &screen_h)
{
	free();

	float scale_x = screen_w / 2560;
	float scale_y = screen_h / 1440;

	knightspecs.load(screen_w, screen_h);

	// Load link buttons.
	github.load			("images/buttons/github.png");
	scores.load			("images/buttons/scores.png");
	website.load		("images/buttons/website.png");
	if (Loading::isError())	return;
	github.setScale		(scale_x, scale_y);
	scores.setScale		(scale_x, scale_y);
	website.setScale	(scale_x, scale_y);
	github.setPosition	(screen_w / 256, screen_h / 144);
	scores.setPosition	(github.getRight() + screen_w / 256, screen_h / 144);
	website.setPosition	(scores.getRight() + screen_w / 256, screen_h / 144);
	github.setUrl		(cmm::GITHUB_FULLPATH);
	scores.setUrl		("empty");
	website.setUrl		(cmm::WEBSITE_FULLPATH);

	// Main buttons.
	singleplayerbutton.load			("images/buttons/singleplayer.png");
	multiplayerbutton.load			("images/buttons/multiplayer.png", true);
	exitbutton.load					("images/buttons/exit.png");
	if (Loading::isError())			return;
	singleplayerbutton.setScale		(scale_x, scale_y);
	multiplayerbutton.setScale		(scale_x, scale_y);
	exitbutton.setScale				(scale_x, scale_y);
	singleplayerbutton.setPosition	(static_cast<float>(screen_w) / 1.9f, static_cast<float>(screen_h) / 2.35f);
	multiplayerbutton.setPosition	(static_cast<float>(screen_w) / 1.9f, singleplayerbutton.getBot() + static_cast<float>(screen_h) / 72.0f);
	exitbutton.setPosition			(static_cast<float>(screen_w) / 1.9f, multiplayerbutton.getBot() + static_cast<float>(screen_h) / 72.0f);
	
	// Circle buttons.
	soundbutton.load			("images/buttons/sound.png");
	musicbutton.load			("images/buttons/music.png");
	updatebutton.load			("images/buttons/update.png");
	reloadbutton.load			("images/buttons/reload.png");
	settingsbutton.load			("images/buttons/settings.png");
	if (Loading::isError())		return;
	soundbutton.setScale		(scale_x, scale_y);
	musicbutton.setScale		(scale_x, scale_y);
	updatebutton.setScale		(scale_x, scale_y);
	reloadbutton.setScale		(scale_x, scale_y);
	settingsbutton.setScale		(scale_x, scale_y);
	soundbutton.setPosition		(screen_w - screen_w / 256 - soundbutton.getWidth(), screen_h - screen_h / 144 - soundbutton.getHeight());
	musicbutton.setPosition		(soundbutton.getLeft() - screen_w / 256 - musicbutton.getWidth(), soundbutton.getTop());
	updatebutton.setPosition	(website.getRight() + screen_w / 256, screen_h / 144);
	reloadbutton.setPosition	(singleplayerbutton.getRight() + screen_w / 256, singleplayerbutton.getTop() + screen_h / 72);
	settingsbutton.setPosition	(musicbutton.getLeft() - screen_w / 256 - settingsbutton.getWidth(), soundbutton.getTop());
	

	// Set volume buttons.
	sound_volumebutton.load			(screen_w, screen_h);
	music_volumebutton.load			(screen_w, screen_h);
	if (Loading::isError())			return;
	sound_volumebutton.setPosition	(soundbutton.getLeft(), soundbutton.getRight(), soundbutton.getBot());
	music_volumebutton.setPosition	(musicbutton.getLeft(), musicbutton.getRight(), musicbutton.getBot());

	// Set chat.
	chat.load(screen_w, screen_h);
	chat.setStyleBlackish();

	information.load	(screen_w, screen_h);
	settings.load		(screen_w, screen_h);
	pausesystem.load	(screen_w, screen_h);
	Loading::add(music.load("music/menu.ogg"));
	if (Loading::isError())	return;
}

void Menu::handle(const sf::Event &event)
{
	if (!isState())
	{
		if (!pausesystem.isActive() && pausesystem.getAlpha() == 0)
		{
			chat.handle(event);

			if (!chat.isActive())
			{
				github.handle				(event);
				scores.handle				(event);
				website.handle				(event);
				singleplayerbutton.handle	(event);
				multiplayerbutton.handle	(event);
				exitbutton.handle			(event);

				if (!sound_volumebutton.handle(event))	soundbutton.handle(event);
				if (!music_volumebutton.handle(event))	musicbutton.handle(event);
				!knightspecs.isReady() || !information.isReady() ? reloadbutton.handle(event) : updatebutton.handle(event);

				settingsbutton.handle		(event);
				settings.handle(event);
			}
		}

		if (!chat.isActive())
		{
			pausesystem.handle(event);
		}
	}
}

void Menu::draw(sf::RenderWindow* &window)
{
	information.draw		(window);
	knightspecs.draw		(window);
	github.draw				(window);
	scores.draw				(window);
	website.draw			(window);
	singleplayerbutton.draw	(window);
	multiplayerbutton.draw	(window);
	exitbutton.draw			(window);
	soundbutton.draw		(window);
	musicbutton.draw		(window);
	!knightspecs.isReady() || !information.isReady() ? reloadbutton.draw(window) : updatebutton.draw(window);
	settingsbutton.draw		(window);
	settings.draw			(window);
	sound_volumebutton.draw	(window);
	music_volumebutton.draw	(window);
	chat.draw				(window);
	pausesystem.draw		(window);
}

void Menu::mechanics(const double &elapsedTime)
{
	set();

	fades(static_cast<float>(elapsedTime));

	// Mechanics.
	if (!pausesystem.isActive() && !isState())
	{
		chat.mechanics(elapsedTime);
		if (chat.isCommand())
		{
			// Close application.
			if (chat.compCommand("@close") || chat.compCommand("@exit"))
			{
				exitbutton.setPressed();
			}

			// Someone clicked singleplayer.
			else if (chat.compCommand("@start") || chat.compCommand("@play"))
			{
				if (knightspecs.isReady() && information.isReady())
				{
					singleplayerbutton.setPressed();
				}
			}

			// Exsert / shovel settings.
			else if (chat.compCommand("@settings") || chat.compCommand("@keyboard"))
			{
				settingsbutton.setActive(!settingsbutton.isActive());
			}

			// Chat changed keys settings so we reload texts
			else if (chat.isNewCoxing())
			{
				if (chat.checkCoxing())
				{
					settings.reloadCoxing();
				}
			}

			// Reload data.
			else if ((!knightspecs.isReady() || !information.isReady()) && (chat.compCommand("@reload")))
			{
				reloadbutton.setActive(true);
			}

			// Update data - works if reload data done its job.
			else if (chat.compCommand("@reload"))
			{
				updatebutton.setActive(true);
			}

			// Turn on/off all sounds.
			else if (chat.compCommand("@sound"))
			{
				cmm::Sound::setGlobalPlayable(!cmm::Sound::getGlobalPlayable());
				soundbutton.setChanged(true);
				soundbutton.setActive(!soundbutton.isActive());
			}
			// Turn on/off music.
			else if (chat.compCommand("@music"))
			{
				cmm::Music::setGlobalPlayable(!cmm::Music::getGlobalPlayable());
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

		knightspecs.mechanics(elapsedTime);

		// Close application.
		if (exitbutton.isPressed())
		{
			chat.isActive() = false;
			exit = true;
		}

		// Someone clicked singleplayer.
		if (singleplayerbutton.isPressed())
		{
			chat.isActive() = false;
			next = true;
		}

		// Exsert / shovel settings.
		settingsbutton.isActive() ? settings.exsertTable(elapsedTime) : settings.shovelTable(elapsedTime);

		// If we dont have answer from database
		!knightspecs.isReady() || !information.isReady() ? singleplayerbutton.lock() : singleplayerbutton.unlock();

		// Update data.
		if (updatebutton.isActive())
		{
			updatebutton.setActive(false);
			knightspecs.reloadThread();
			information.reloadThread();
			knightspecs.setThread();
			information.setThread();
		}

		// Reload data.
		if (reloadbutton.isActive())
		{
			reloadbutton.setActive(false);
			if (!knightspecs.isReady())	knightspecs.setThread();
			if (!information.isReady())	information.setThread();
		}

		settings.mechanics(elapsedTime);
		information.mechanics();
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
			cmm::Sound::setGlobalVolume		(value);
			// knightspecs.setVolume			(value);
			github.setVolume				(value);
			scores.setVolume				(value);
			website.setVolume				(value);
			singleplayerbutton.setVolume	(value);
			multiplayerbutton.setVolume		(value);
			exitbutton.setVolume			(value);
			soundbutton.setVolume			(value);
			musicbutton.setVolume			(value);
			settingsbutton.setVolume		(value);
			settings.setVolume				(value);
			sound_volumebutton.setVolume	(value);
			music_volumebutton.setVolume	(value);
			pausesystem.setVolume			(value);
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
			cmm::Music::setGlobalVolume	(value);
			music.setVolume				(value);
		}
	}
}

void Menu::setState(int &state)
{
	if (isPrev())
	{
		reset();
		state = cmm::STATES::EDITOR;
	}
	else if (isNext())
	{
		reset();
		state = cmm::STATES::LEVELMENU;
	}
	else if (isExit())
	{
		reset();
		cmm::StaticCore::open = false;
	}
}

void Menu::fades(const float &elapsedTime)
{
	if (pausesystem.isActive())
	{
		float value = elapsedTime * MAX_ALPHA * 2;
		int min = (int)MAX_ALPHA * 3 / 4;
		fadeout(value, min);
		pausesystem.fadein(value * 3, min);
		music.fadeout(elapsedTime * 100, static_cast<int>(music_volumebutton.getGlobalVolume() * 0.2));
	}
	else if (isState())
	{
		int min = 0;
		fadeout(elapsedTime * MAX_ALPHA, min);
		music.fadeout(elapsedTime * 100, min);
	}
	else
	{
		float value = elapsedTime * MAX_ALPHA * 2;
		int max = (int)MAX_ALPHA, min = (int)MIN_ALPHA;
		fadein(value, max);
		pausesystem.fadeout(value, min);
		music.fadein(elapsedTime * 100, static_cast<int>(music_volumebutton.getGlobalVolume()));
	}
}

void Menu::fadein(const float &value, const int &max)
{
	knightspecs.fadein			(value, max);
	github.fadein				(value, max);
	scores.fadein				(value, max);
	website.fadein				(value, max);
	singleplayerbutton.fadein	(value, max);
	multiplayerbutton.fadein	(value, max);
	exitbutton.fadein			(value, max);
	soundbutton.fadein			(value, max);
	musicbutton.fadein			(value, max);
	updatebutton.fadein			(value, max);
	reloadbutton.fadein			(value, max);
	settingsbutton.fadein		(value, max);
	settings.fadein				(value, max);
	sound_volumebutton.fadein	(value, max);
	music_volumebutton.fadein	(value, max);
	information.fadein			(value, max);
}

void Menu::fadeout(const float &value, const int &min)
{
	knightspecs.fadeout			(value, min);
	github.fadeout				(value, min);
	scores.fadeout				(value, min);
	website.fadeout				(value, min);
	singleplayerbutton.fadeout	(value, min);
	multiplayerbutton.fadeout	(value, min);
	exitbutton.fadeout			(value, min);
	soundbutton.fadeout			(value, min);
	musicbutton.fadeout			(value, min);
	updatebutton.fadeout		(value, min);
	reloadbutton.fadeout		(value, min);
	settingsbutton.fadeout		(value, min);
	settings.fadeout			(value, min);
	sound_volumebutton.fadeout	(value, min);
	music_volumebutton.fadeout	(value, min);
	information.fadeout			(value, min);
	chat.fadeout				(value, min);
}