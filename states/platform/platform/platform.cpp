#include "platform.h"
#include "core.h"	// StaticCore
#include "scontent.h"

Platform::Platform()
{
	free();
}

Platform::~Platform()
{
	free();
}

void Platform::free()
{
	prev = false;
	next = false;
	exit = false;
	loaded = false;

	homebutton.free();
	levelbutton.free();
	soundbutton.free();
	musicbutton.free();
	sound_volumebutton.free();
	music_volumebutton.free();
	movingBG.free();
	chat.free();
	pausesystem.free();
}

void Platform::set()
{
	if (!loaded)
	{
		loaded = true;

		// Set threads.
		// ...

		// Sound.
		bool soundPlayable = cmm::Sound::getGlobalPlayable();
		float soundVolume = cmm::Sound::getGlobalVolume();

		homebutton.setVolume(soundVolume);
		levelbutton.setVolume(soundVolume);
		soundbutton.setVolume(soundVolume);
		musicbutton.setVolume(soundVolume);
		sound_volumebutton.setVolume(soundVolume);
		sound_volumebutton.setGlobalVolume(soundVolume);
		music_volumebutton.setVolume(soundVolume);
		pausesystem.setVolume(soundVolume);
		soundbutton.setActive(soundPlayable);

		// Music.
		bool musicPlayable = cmm::Music::getGlobalPlayable();
		float musicVolume = cmm::Music::getGlobalVolume();

		music.setVolume(musicVolume);
		music_volumebutton.setGlobalVolume(musicVolume);
		musicbutton.setActive(musicPlayable);
		musicbutton.isActive() ? music.play() : music.pause();

		prepare();
	}
}

bool Platform::isReady() const
{
	return movingBG.getAlpha() == 0.0f;
}

void Platform::reset()
{
	prev = false;
	next = false;
	exit = false;
	loaded = false;
	
	homebutton.setActive(false);
	levelbutton.setActive(false);

	// Action
	knight.reset();
	eye.reset(knight.getRect());
	tiles.reset();
	// ---

	chat.reset();
	music.stop();
}

void Platform::load(const float &screen_w, const float &screen_h)
{
	free();

	float scale_x = screen_w / 2560;
	float scale_y = screen_h / 1440;

	// Circle buttons.
	homebutton.load("images/buttons/home.png");
	levelbutton.load("images/buttons/levelmenu.png");
	soundbutton.load("images/buttons/sound.png");
	musicbutton.load("images/buttons/music.png");
	homebutton.setScale(scale_x, scale_y);
	levelbutton.setScale(scale_x, scale_y);
	soundbutton.setScale(scale_x, scale_y);
	musicbutton.setScale(scale_x, scale_y);
	homebutton.setPosition(screen_w / 256, screen_h / 144);
	levelbutton.setPosition(homebutton.getRight() + screen_w / 256, homebutton.getTop());
	soundbutton.setPosition(screen_w - screen_w / 256 - soundbutton.getWidth(), screen_h - screen_h / 144 - soundbutton.getHeight());
	musicbutton.setPosition(soundbutton.getLeft() - screen_w / 256 - musicbutton.getWidth(), soundbutton.getTop());

	// Set volume buttons.
	sound_volumebutton.load(screen_w, screen_h);
	music_volumebutton.load(screen_w, screen_h);
	sound_volumebutton.setPosition(soundbutton.getLeft(), soundbutton.getRight(), soundbutton.getBot());
	music_volumebutton.setPosition(musicbutton.getLeft(), musicbutton.getRight(), musicbutton.getBot());

	// Action ---
	movingBG.load(screen_w, screen_h);
	knight.load(screen_w, screen_h);
	eye.load(screen_w, screen_h);
	tiles.load(screen_w, screen_h);
	// ----------

	// Set chat.
	chat.load(screen_w, screen_h);
	chat.setStyleWhitish();

	pausesystem.load(screen_w, screen_h);
	music.load("music/platform/common.ogg");
}

void Platform::handle(const sf::Event &event)
{
	if (!isState())
	{
		if (!pausesystem.isActive() && pausesystem.getAlpha() == 0)
		{
			chat.handle(event);

			if (!chat.isActive())
			{
				homebutton.handle(event);
				levelbutton.handle(event);

				knight.handle(event);

				if (!sound_volumebutton.handle(event))	soundbutton.handle(event);
				if (!music_volumebutton.handle(event))	musicbutton.handle(event);
			}
		}

		if (!chat.isActive())
		{
			pausesystem.handle(event);
		}
	}
}

void Platform::draw(sf::RenderWindow* &window)
{
	movingBG.draw			(window);
	window->setView(eye.getView());				// ---------------
	knight.draw				(window);
	eye.draw				(window);
	tiles.draw				(window);
	window->setView(window->getDefaultView());	// ---------------

	homebutton.draw			(window);
	levelbutton.draw		(window);
	soundbutton.draw		(window);
	musicbutton.draw		(window);
	sound_volumebutton.draw	(window);
	music_volumebutton.draw	(window);
	chat.draw				(window);
	pausesystem.draw		(window);
}

void Platform::mechanics(const double &elapsedTime)
{
	set();

	fades(static_cast<float>(elapsedTime));

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
			else if (chat.compCommand("@menu") || chat.compCommand("@home"))
				homebutton.setActive(true);
			else if (chat.compCommand("@levelmenu"))
				levelbutton.setActive(true);

			else if (chat.isNewCoxing())
			{
				if (chat.checkCoxing())
				{
					// ...?
				}
			}
			
			else if (SContent::type != SContent::TYPE::SERVER && chat.compCommand("@collision"))
			{
				knight.switchCollision();
				tiles.switchCollision();
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
			else
				chat.setError();
		}

		const float floatElapsedTime = static_cast<float>(elapsedTime);
		knight.mechanics(floatElapsedTime);
		knight.gravity();
		if (tiles.checkCollisionV(knight.getRect(), -1))
			knight.undoGravity();
		
		if (knight.moveLeft(floatElapsedTime))
		{
			if (tiles.checkCollisionH(knight.getRect(), 2))
				knight.undoMoveLeft(floatElapsedTime);
		}
		else if (knight.moveRight(floatElapsedTime))
		{
			if (tiles.checkCollisionH(knight.getRect(), -2))
				knight.undoMoveRight(floatElapsedTime);
		}
		else
			knight.idle(floatElapsedTime);
		if (knight.jump(floatElapsedTime))
		{
			if (tiles.checkCollisionV(knight.getRect(), 1))
				knight.undoJump(floatElapsedTime);
		}
		knight.attack();
		knight.rest();
		eye.mechanics(floatElapsedTime, knight.getRect(), knight.isLeftAligned());

		float direction = 0;
		movingBG.mechanics(static_cast<float>(elapsedTime), direction);
		
		if (homebutton.isActive())
		{
			chat.isActive() = false;
			prev = true;
			next = true;
		}
		
		if (levelbutton.isActive())
		{
			chat.isActive() = false;
			prev = true;
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
			homebutton.setVolume(value);
			levelbutton.setVolume(value);
			soundbutton.setVolume(value);
			musicbutton.setVolume(value);
			sound_volumebutton.setVolume(value);
			music_volumebutton.setVolume(value);
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
			music.setVolume(music_volumebutton.getGlobalVolume());
		}
	}
}

void Platform::setState(int &state)
{
	if (isPrev() && isNext())
	{
		reset();
		state = cmm::MENU;
	}
	else if (isPrev())
	{
		reset();
		if (SContent::type == SContent::TYPE::EDITOR)
			state = cmm::STATES::EDITOR;
		else
			state = cmm::STATES::LEVELMENU;
	}
	else if (isNext())
	{

	}
	else if (isExit())
	{
		reset();
		cmm::StaticCore::open = false;
	}
}

void Platform::fades(const float &elapsedTime)
{
	if (pausesystem.isActive())
	{
		float value = elapsedTime * 0xFF * 2;
		int min = 0xFF * 3 / 4;
		fadeout(value, min);
		pausesystem.fadein(value * 3, min);
		music.fadeout(elapsedTime * 100, static_cast<int>(music_volumebutton.getGlobalVolume() * 0.2));
	}
	else if (isState())
	{
		int min = 0;
		fadeout(elapsedTime * 0xFF, min);
		music.fadeout(elapsedTime * 100, min);
	}
	else
	{
		float value = elapsedTime * 0xFF * 2;
		int max = 0xFF, min = 0;
		fadein(value, max);
		pausesystem.fadeout(value, min);
		music.fadein(elapsedTime * 100, static_cast<int>(music_volumebutton.getGlobalVolume()));
	}
}

void Platform::fadein(const float &value, const int &max)
{
	homebutton.fadein(value, max);
	levelbutton.fadein(value, max);
	soundbutton.fadein(value, max);
	musicbutton.fadein(value, max);
	sound_volumebutton.fadein(value, max);
	music_volumebutton.fadein(value, max);
}

void Platform::fadeout(const float &value, const int &min)
{
	homebutton.fadeout(value, min);
	levelbutton.fadeout(value, min);
	soundbutton.fadeout(value, min);
	musicbutton.fadeout(value, min);
	sound_volumebutton.fadeout(value, min);
	music_volumebutton.fadeout(value, min);
	chat.fadeout(value, min);
}

void Platform::prepare()
{
	// Load modules here...
	// The data has been simulated, so here we do not check it.
	knight.read(SContent::get(SContent::category().KNIGHT)[0]);
	eye.reset(knight.getRect());
	tiles.read(SContent::get(SContent::category().TILE));
	tiles.read(SContent::get(SContent::category().UNVISIBLE_TILE));
}
