#include "menu.h"
#include "boost/lexical_cast.hpp"
#include <fstream>

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

	// knight_specs.free();
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
	// chat.free();
	pausesystem.free();
}

void Menu::set()
{
	if (!loaded)
	{
		loaded = true;

		// Set threads.
		// knight_specs.setThread();
		information.setThread();

		// Sound.
		float soundVolume = 50;
		// knight_specs.setVolume			(soundVolume);
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
		cmm::Sound::setPlayable	(true);
		soundbutton.setActive	(true);

		// Music.
		float musicVolume = 60;
		music.setVolume						(musicVolume);
		music_volumebutton.setGlobalVolume	(musicVolume);
		cmm::Music::setPlayable	(true);
		musicbutton.setActive	(true);
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

	// knight_specs.reload();
	singleplayerbutton.reset();
	settingsbutton.setActive(false);
	settings.reload();
	// chat.reset();
	music.stop();
}



void Menu::load(float screen_w, float screen_h)
{
	free();

	float scale_x = screen_w / 2560;
	float scale_y = screen_h / 1440;

	// knight_specs.load( screen_w, screen_h );

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
	website.setUrl		("http://adrianmichalek.pl/combathalloween/");

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
	/*chat.load(screen_w, screen_h);
	chat.setCommandColor(sf::Color(0, 0, 0));
	chat.setTypicalColor(sf::Color(0x68, 0x68, 0x68));*/

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
			// chat.handle(event);

			// if (!chat.isOpen())
			// {
				// knight_specs.handle		(event);
				github.handle				(event);
				scores.handle				(event);
				website.handle				(event);
				singleplayerbutton.handle	(event);
				multiplayerbutton.handle	(event);
				exitbutton.handle			(event);

				if (!sound_volumebutton.handle(event))	soundbutton.handle(event);
				if (!music_volumebutton.handle(event))	musicbutton.handle(event);
				// !knight_specs.isReady() || !information.isReady() ? reloadbutton.handle(event) : updatebutton.handle(event);

				settingsbutton.handle		(event);
				settings.handle				(event);
			// }
		}

		// if (!chat.isOpen())
		// {
			pausesystem.handle(event);
		// }
	}
}

void Menu::head(sf::RenderWindow* &window, double elapsedTime)
{
	set();
	mechanics(elapsedTime);
	fades(elapsedTime);
	draw(window);
}



void Menu::draw(sf::RenderWindow* &window)
{
	information.draw		(window);
	// knight_specs.draw	(window);
	github.draw				(window);
	scores.draw				(window);
	website.draw			(window);
	singleplayerbutton.draw	(window);
	multiplayerbutton.draw	(window);
	exitbutton.draw			(window);
	soundbutton.draw		(window);
	musicbutton.draw		(window);
	// !knight_specs.isReady() || !information.isReady() ? reloadbutton.draw(window) : updatebutton.draw(window);
	settingsbutton.draw		(window);
	settings.draw			(window);
	sound_volumebutton.draw	(window);
	music_volumebutton.draw	(window);
	// chat.draw			(window);
	pausesystem.draw		(window);
}

void Menu::mechanics(double elapsedTime)
{
	// Mechanics.
	if (!pausesystem.isActive() && !isState())
	{
		//chat.mechanics(elapsedTime);
		//if (chat.isCommand())
		//{
		//	// Knight specs.
		//	if (chat.findCommand("@clear"))			knight_specs.setChosen(-1);
		//	else if (chat.findCommand("@helmet"))	knight_specs.setChosen(0);
		//	else if (chat.findCommand("@body"))		knight_specs.setChosen(1);
		//	else if (chat.findCommand("@shield"))	knight_specs.setChosen(2);
		//	else if (chat.findCommand("@sword"))		knight_specs.setChosen(3);
		//	else if (chat.findCommand("@boots"))		knight_specs.setChosen(4);

		//	// Close application.
		//	else if (chat.findCommand("@close") || chat.findCommand("@exit"))
		//	{
		//		exit.setPressed();
		//	}

		//	// Someone clicked singleplayer.
		//	else if (chat.findCommand("@start") || chat.findCommand("@play"))
		//	{
		//		if (knight_specs.isReady() && information.isReady())
		//		{
		//			singleplayer.setPressed();
		//		}
		//	}

		//	// Exsert / shovel settings.
		//	else if (chat.findCommand("@settings") || chat.findCommand("@keyboard") ||
		//		chat.findCommand("@keys") || chat.findCommand("@sets"))
		//	{
		//		settingsbutton.setActive(!settingsbutton.isActive());
		//	}

		//	// Reload data.
		//	else if (chat.findCommand("@reload") || chat.findCommand("@connect") ||
		//		chat.findCommand("@rel") || chat.findCommand("@con"))
		//	{
		//		reloadbutton.setActive(true);
		//	}

		//	// Update data.
		//	else if (chat.findCommand("@update"))
		//	{
		//		updatebutton.setActive(true);
		//	}

		//	// Turn on/off all chunks.
		//	else if (chat.findCommand("@chunk"))
		//	{
		//		chunkbutton.setChanged(true);
		//		chunkbutton.setActive(!chunkbutton.isActive());
		//	}

		//	// Turn on/off music.
		//	else if (chat.findCommand("@music"))
		//	{
		//		musicbutton.setChanged(true);
		//		musicbutton.setActive(!musicbutton.isActive());
		//	}

		//	// Turn on/off all sounds.
		//	else if (chat.findCommand("@sound"))
		//	{
		//		chunkbutton.setChanged(true);
		//		chunkbutton.setActive(!chunkbutton.isActive());
		//		musicbutton.setChanged(true);
		//		musicbutton.setActive(!musicbutton.isActive());
		//	}

		//	// Map editor.
		//	else if (chat.findCommand("@editor") || chat.findCommand("@edit"))
		//	{
		//		editor = true;
		//		chat.isOpen() = false;
		//	}

		//	// Link buttons in addition.
		//	else if (chat.findCommand("@github"))		github.openWebsite();
		//	else if (chat.findCommand("@scores"))		scores.openWebsite();
		//	else if (chat.findCommand("@website"))	website.openWebsite();

		//	// Tell that command doesn't exist.
		//	else
		//	{
		//		chat.setError();
		//	}
		//}

		// Knight specs
		// knight_specs.mechanics(elapsedTime);


		// Close application.
		if (exitbutton.isPressed())
		{
			// chat.isOpen() = false;
			exit = true;
		}


		// Someone clicked singleplayer.
		if (singleplayerbutton.isPressed())
		{
			// chat.isOpen() = false;
			next = true;
		}


		// Exsert / shovel settings.
		settingsbutton.isActive() ? settings.exsertTable(elapsedTime) : settings.shovelTable(elapsedTime);

		// If we dont have answer from database
		// !knight_specs.isReady() || !information.isReady() ? singleplayerbutton.lock() : singleplayerbutton.unlock();

		// update data
		if (updatebutton.isActive())
		{
			updatebutton.setActive(false);

			if (/*knight_specs.isReady() && */information.isReady())
			{
				// knight_specs.reloadValues();
				// knight_specs.setThread();
				information.reloadMoney();
				information.setThread();
			}
		}

		// reload data
		if (reloadbutton.isActive())
		{
			reloadbutton.setActive(false);
			/*if (!knight_specs.isReady())
			{
				knight_specs.setThread();
			}*/

			if (!information.isReady())
			{
				information.setThread();
			}
		}

		settings.mechanics(elapsedTime);
		information.mechanics();
		sound_volumebutton.mechanics(elapsedTime);
		music_volumebutton.mechanics(elapsedTime);

		// Turn on/off all sounds.
		if (soundbutton.hasChanged())
		{
			cmm::Sound::setPlayable(soundbutton.isActive());
		}

		// Volume of sounds is changed.
		if (sound_volumebutton.hasChanged())
		{
			float value = sound_volumebutton.getGlobalVolume();
			// knight_specs.setVolume		(value);
			github.setVolume				(value);
			scores.setVolume				(value);
			website.setVolume				(value);
			singleplayerbutton.setVolume	(value);
			multiplayerbutton.setVolume		(value);
			exitbutton.setVolume			(value);
			soundbutton.setVolume			(value);
			musicbutton.setVolume			(value);
			settingsbutton.setVolume		(value);
			sound_volumebutton.setVolume	(value);
			music_volumebutton.setVolume	(value);
			pausesystem.setVolume			(value);
		}

		// Turn on/off music.
		if (musicbutton.hasChanged())
		{
			cmm::Music::setPlayable(musicbutton.isActive());
			musicbutton.isActive() ? music.play() : music.pause();
		}

		// Volume of music is changed.
		if (music_volumebutton.hasChanged())
		{
			music.setVolume(music_volumebutton.getGlobalVolume());
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
	// knight_specs.fadein		(value, max);
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
	// knight_specs.fadeout		(value, min);
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
	// chat.fadeout				(value, min);
}