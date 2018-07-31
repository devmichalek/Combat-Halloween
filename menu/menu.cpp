#include "menu.h"
#include "boost/lexical_cast.hpp"

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
		settings.setThread();

		// Sound.
		float soundVolume = 50;
		cmm::Sound::setGlobalVolume			(soundVolume);
		knightspecs.setVolume				(soundVolume);
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
		cmm::Sound::setGlobalPlayable		(true);
		soundbutton.setActive				(true);

		// Music.
		float musicVolume = 60;
		cmm::Music::setGlobalVolume			(musicVolume);
		music.setVolume						(musicVolume);
		music_volumebutton.setGlobalVolume	(musicVolume);
		cmm::Music::setGlobalPlayable		(true);
		musicbutton.setActive				(true);
		music.play();
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
	music.stop();
}



void Menu::load(float screen_w, float screen_h)
{
	free();

	float scale_x = screen_w / 2560;
	float scale_y = screen_h / 1440;

	knightspecs.load(screen_w, screen_h);

	// Load link buttons.
	github.load			("images/buttons/github.png");
	scores.load			("images/buttons/scores.png");
	website.load		("images/buttons/website.png");
	github.setScale		(scale_x, scale_y);
	scores.setScale		(scale_x, scale_y);
	website.setScale	(scale_x, scale_y);
	github.setPosition	(screen_w / 256, screen_h / 144);
	scores.setPosition	(github.getRight() + screen_w / 256, screen_h / 144);
	website.setPosition	(scores.getRight() + screen_w / 256, screen_h / 144);
	github.setUrl		("https://github.com/devmichalek/Combat-Halloween");
	scores.setUrl		("empty");
	website.setUrl		("http://combathalloween.netne.net/");

	// Main buttons.
	singleplayerbutton.load			("images/buttons/singleplayer.png");
	multiplayerbutton.load			("images/buttons/multiplayer.png", true);
	exitbutton.load					("images/buttons/exit.png");
	singleplayerbutton.setScale		(scale_x, scale_y);
	multiplayerbutton.setScale		(scale_x, scale_y);
	exitbutton.setScale				(scale_x, scale_y);
	singleplayerbutton.setPosition	(screen_w / 1.9, screen_h / 2.35);
	multiplayerbutton.setPosition	(screen_w / 1.9, singleplayerbutton.getBot() + screen_h / 72);
	exitbutton.setPosition			(screen_w / 1.9, multiplayerbutton.getBot() + screen_h / 72);
	
	// Circle buttons.
	soundbutton.load			("images/buttons/sound.png");
	musicbutton.load			("images/buttons/music.png");
	updatebutton.load			("images/buttons/update.png");
	reloadbutton.load			("images/buttons/reload.png");
	settingsbutton.load			("images/buttons/settings.png");
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
	sound_volumebutton.setPosition	(soundbutton.getLeft(), soundbutton.getRight(), soundbutton.getBot());
	music_volumebutton.setPosition	(musicbutton.getLeft(), musicbutton.getRight(), musicbutton.getBot());

	// Set chat.
	chat.load(screen_w, screen_h);
	chat.setCommandColor(sf::Color(0, 0, 0));
	chat.setTypicalColor(sf::Color(0x68, 0x68, 0x68));

	information.load	(screen_w, screen_h);
	settings.load		(screen_w, screen_h);
	pausesystem.load	(screen_w, screen_h);
	music.load("music/menu.ogg");
}

void Menu::handle(sf::Event& event)
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
				!knightspecs.isReady() || !information.isReady() || !settings.isReady() ? reloadbutton.handle(event) : updatebutton.handle(event);

				settingsbutton.handle		(event);
				if(settings.isReady())		settings.handle(event);
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
	!knightspecs.isReady() || !information.isReady() || !settings.isReady() ? reloadbutton.draw(window) : updatebutton.draw(window);
	settingsbutton.draw		(window);
	settings.draw			(window);
	sound_volumebutton.draw	(window);
	music_volumebutton.draw	(window);
	chat.draw				(window);
	pausesystem.draw		(window);
}

void Menu::mechanics(double elapsedTime)
{
	set();

	fades(elapsedTime);

	// FPS.
	/*FPS::mechanics(elapsedTime);
	if (FPS::timePassed())
	{
		printf("%d\n", FPS::getFPS());
	}*/

	// Mechanics.
	if (!pausesystem.isActive() && !isState())
	{
		chat.mechanics(elapsedTime);
		if (chat.isCommand())
		{
			// Close application.
			if (chat.findCommand("@close") || chat.findCommand("@exit"))
			{
				exitbutton.setPressed();
			}

			// Someone clicked singleplayer.
			else if (chat.findCommand("@start") || chat.findCommand("@play"))
			{
				if (knightspecs.isReady() && information.isReady() && settings.isReady())
				{
					singleplayerbutton.setPressed();
				}
			}

			// Exsert / shovel settings.
			else if (chat.findCommand("@settings") || chat.findCommand("@keyboard") ||
				chat.findCommand("@keys") || chat.findCommand("@sets"))
			{
				settingsbutton.setActive(!settingsbutton.isActive());
			}

			// Reload data.
			else if ((!knightspecs.isReady() || !information.isReady() || !settings.isReady()) &&
				(chat.findCommand("@reload") || chat.findCommand("@rel")))
			{
				reloadbutton.setActive(true);
			}

			// Update data - works if reload data done its job.
			else if (chat.findCommand("@reload") || chat.findCommand("@rel"))
			{
				updatebutton.setActive(true);
			}

			// Turn on/off all sounds.
			else if (chat.findCommand("@sound"))
			{
				cmm::Sound::setGlobalPlayable(!cmm::Sound::getGlobalPlayable());
				soundbutton.setChanged(true);
				soundbutton.setActive(!soundbutton.isActive());
			}

			// Turn on/off music.
			else if (chat.findCommand("@music"))
			{
				cmm::Music::setGlobalPlayable(!cmm::Music::getGlobalPlayable());
				musicbutton.setChanged(true);
				musicbutton.setActive(!musicbutton.isActive());
			}

		//	// Map editor.
		//	else if (chat.findCommand("@mapeditor"))
		//	{
		//		editor = true;
		//		chat.isOpen() = false;
		//	}

			// Link buttons in addition.
			else if (chat.findCommand("@github"))		github.openWebsite();
			else if (chat.findCommand("@scores"))		scores.openWebsite();
			else if (chat.findCommand("@website"))		website.openWebsite();

			// Command doesn't exist.
			else
			{
				chat.setError();
			}
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
		!knightspecs.isReady() || !information.isReady() || !settings.isReady() ? singleplayerbutton.lock() : singleplayerbutton.unlock();

		// Update data.
		if (updatebutton.isActive())
		{
			updatebutton.setActive(false);
			knightspecs.reloadThread();
			information.reloadThread();
			settings.reloadThread();
			knightspecs.setThread();
			information.setThread();
			settings.setThread();
		}

		// Reload data.
		if (reloadbutton.isActive())
		{
			reloadbutton.setActive(false);
			if (!knightspecs.isReady())	knightspecs.setThread();
			if (!information.isReady())	information.setThread();
			if (!settings.isReady())	settings.setThread();
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
			knightspecs.setVolume			(value);
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

void Menu::fades(double elapsedTime)
{
	if (pausesystem.isActive())
	{
		float value = elapsedTime * 0xFF * 2, min = 0xFF * 3 / 4;
		fadeout(value, min);
		pausesystem.fadein(value * 3, min);
		music.fadeout(elapsedTime * 100, music_volumebutton.getGlobalVolume() *0.2);
	}
	else if (isState())
	{
		fadeout(elapsedTime * 0xFF);
		music.fadeout(elapsedTime * 100);
	}
	else
	{
		float value = elapsedTime * 0xFF * 2;
		fadein(value);
		pausesystem.fadeout(value);
		music.fadein(elapsedTime * 100, music_volumebutton.getGlobalVolume());
	}
}

void Menu::fadein(float value, int max)
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

void Menu::fadeout(float value, int min)
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