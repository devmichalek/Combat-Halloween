<<<<<<< HEAD
/**
    menu.h
    Purpose: class Menu is a huge container with buttons in menu state.

    @author Adrian Michalek
    @version 2016.11.20
	@email adrmic98@gmail.com
*/

#include "menu.h"

Menu::Menu()
{
	state = 0;
	
	// Create menu objects
	title = new Title;
	
	music_button = new Sound_button;
	chunk_button = new Sound_button( false );
	
	music_volume = new Volume_button( 64 );	// 50% of 128, 128 is max value.
	chunk_volume = new Volume_button( 52 );	// 40% of 128
	
	git_button = new Link_button( "https://github.com/Adriqun/Assassin-s-Genesis" );
	google_button = new Link_button( "http://ag2d.netne.net/" );
	twitter_button = new Link_button( "", true );
	facebook_button = new Link_button( "", true );
	scores_button = new Link_button( "http://ag2d.netne.net/#section4" );
	
	play_button = new Play_button;
	
	author_log = new Log;
	game_log = new Log;
	settings_log = new Log;
	skill_log = new Log;
	
	exit = new Exit_log;
	
	music = new Music; music->setID( "menu-music" );
	
	information = new Information;
	keyboard = new Keyboard;
	
	development = new Development;
	headdeck = new Headdeck;
	
	reset_button = new Reset_button;
	
	nick = new Nick;
	author = new Author;
=======
#include "menu.h"
#include "own/file.h"

Menu::Menu()
{
	free();
>>>>>>> Combat-Halloween/master
}

Menu::~Menu()
{
	free();
}

void Menu::free()
{
<<<<<<< HEAD
	delete title;
	delete music_button;
	delete chunk_button;
	delete music_volume;
	delete chunk_volume;
	delete git_button;
	delete google_button;
	delete twitter_button;
	delete facebook_button;
	delete scores_button;
	delete play_button;
	delete author_log;
	delete game_log;
	delete settings_log;
	delete skill_log;
	delete exit;
	delete music;
	delete information;
	delete keyboard;
	delete development;
	delete headdeck;
	delete reset_button;
	delete nick;
	delete author;
=======
	ready = false;
	close = false;
	editor = false;
	run = false;
	
	background.free();
	knight_specs.free();
	github.free();
	scores.free();
	website.free();
	singleplayer.free();
	multiplayer.free();
	exit.free();
	chunkbutton.free();
	musicbutton.free();
	updatebutton.free();
	reloadbutton.free();
	settingsbutton.free();
	settings.free();
	chunk_volume.free();
	music_volume.free();
	information.free();
	chat.free();
	pausesystem.free();
	music.free();
>>>>>>> Combat-Halloween/master
}



<<<<<<< HEAD
void Menu::load( unsigned screen_w, unsigned screen_h )
{
	// title art
	title->load( screen_w, screen_h );
	
	// sound buttons
	music_button->load( "data/menu/music.png" );
	music_button->setExplanator( "Turn on/off music." );	
	chunk_button->load( "data/menu/chunk.png", music_button->getBot() );
	chunk_button->setExplanator( "Turn on/off chunks." );
	
	// volume buttons
	music_volume->load( screen_w, screen_h/2 -screen_h /7, "Music" );
	chunk_volume->load( screen_w, music_volume->getBot() + 25, "Sound" );
	
	// chunk volume
	sound.setChunkPlay( true );
	sound.setChunkVolume( chunk_volume->getVolume() );
	
	// music volume
	sound.setMusicPlay( true );
	sound.setMusicVolume( music_volume->getVolume() );
	
	// link buttons
	git_button->load( "data/menu/git.png", screen_w, 10 );
	git_button->setExplanator( "Visit github!" );
	google_button->load( "data/menu/google.png", screen_w, git_button->getBot() );
	google_button->setExplanator( "Visit ag2d.netne.net!" );
	twitter_button->load( "data/menu/twitter.png", screen_w, google_button->getBot() );
	twitter_button->setExplanator( "Twitter? Not today..." );
	facebook_button->load( "data/menu/facebook.png", screen_w, twitter_button->getBot() );
	facebook_button->setExplanator( "Damm, who needs facebook?" );
	scores_button->load( "data/menu/scores.png", git_button->getWidth() +20, screen_h -git_button->getHeight() -10 );
	scores_button->setExplanator( "Sorry dude, it's not ready" );
	
	// button to start game
	play_button->load( screen_w, screen_h );
	
	// logs
	author_log->load( "author", play_button->getX() +11, play_button->getBot() );
	author_log->setExplanator( "Champions" );
	game_log->load( "game", author_log->getRight() -5, play_button->getBot() );
	game_log->setExplanator( "Meet your makers" );
	settings_log->load( "settings", game_log->getRight() -2, play_button->getBot() );
	settings_log->setExplanator( "Go to the settings." );
	skill_log->load( "skill", settings_log->getRight() -4, play_button->getBot() );
	skill_log->setExplanator( "Manage skills." );
	
	// exit log
	exit->load( screen_w, screen_h );
	
	// music for menu
	music->load( "data/menu/music.mp3", 50 );
	
	// information (keyboard) and keyboard
	keyboard->load( screen_w, screen_h, screen_h/2 + screen_h /6 );
	information->load( screen_w, screen_h, screen_h/2 - screen_h /7, keyboard->getSaveY() );
	
	development->load( screen_w, screen_h, title->getBot() +28 );
	headdeck->load( screen_w, screen_h, title->getBot() +(screen_h /8) );
	
	reset_button->load( screen_w, screen_h );
	
	nick->load( screen_w, screen_h, game_log->getXCenter(), settings_log->getBot() );
	author->load( screen_w, screen_h, title->getBot() );
	
	//Set start volume
	music_button->setVolume( chunk_volume->getVolume() );
	chunk_button->setVolume( chunk_volume->getVolume() );
	music_volume->setVolume( chunk_volume->getVolume() );
	chunk_volume->setVolume( chunk_volume->getVolume() );
	git_button->setVolume( chunk_volume->getVolume() );
	google_button->setVolume( chunk_volume->getVolume() );
	play_button->setVolume( chunk_volume->getVolume() );
	author_log->setVolume( chunk_volume->getVolume() );
	game_log->setVolume( chunk_volume->getVolume() );
	skill_log->setVolume( chunk_volume->getVolume() );
	settings_log->setVolume( chunk_volume->getVolume() );
	exit->setVolume( chunk_volume->getVolume() );
	keyboard->setVolume( chunk_volume->getVolume() );
	development->setVolume( chunk_volume->getVolume() );
	headdeck->setVolume( chunk_volume->getVolume() );
	reset_button->setVolume( chunk_volume->getVolume() );
}

void Menu::handle( sf::Event &event )
{
	if( play_button->getState() != 2 ) // if user didn't click play
	{
		if( reset_button->getState() == 0 )
		{
			exit->handle( event );
		}
		
		if( !author_log->getState() &&
			!game_log->getState() &&
			!skill_log->getState() &&
			!settings_log->getState() &&
			exit->getState() == 0 )
		{
			reset_button->handle( event );
		}

		if( exit->getState() == 0 && reset_button->getState() == 0 ) // if user didn't click quit
		{
			if( !author_log->getState() &&
				!skill_log->getState() &&
				!settings_log->getState() &&
				!game_log->getState() ) // if user didn't click logs
			{
				git_button->handle( event );
				google_button->handle( event );
				twitter_button->handle( event );
				facebook_button->handle( event );
				scores_button->handle( event, true );
				play_button->handle( event );
				music_button->handle( event );
				chunk_button->handle( event );
			}
				
			if( !author_log->getState() && !settings_log->getState() && !game_log->getState() )
			{
				skill_log->handle( event );
			}
			if( !skill_log->getState() && !settings_log->getState() && !game_log->getState() )
			{
				author_log->handle( event );
			}
			if( !skill_log->getState() && !author_log->getState() && !game_log->getState() )
			{
				if( settings_log->handle( event ) )
				{
					nick->setShow();
				}
			}
			if( !skill_log->getState() && !author_log->getState() && !settings_log->getState() )
			{
				game_log->handle( event );
			}
				
			if( skill_log->getState() )
			{
				development->handle( event );
			}
			
			if( author_log->getState() )
			{
				headdeck->handle( event );
			}
				
			if( settings_log->getState() )
			{
				music_volume->handle( event );
				chunk_volume->handle( event );
				keyboard->handle( event );
			}
			
			if( game_log->getState() )
			{
				author->handle( event );
			}
		}
	}
}

void Menu::draw( sf::RenderWindow* &window )
{
	// Play music if true
	if( sound.getMusicPlay() )
	{
		music->play();
	}
		
	// Turn off/on music
	if( music_button->isChanged() )
	{
		music->pause();
		sound.setMusicPlay( !sound.getMusicPlay() );
	}
	
	// Turn off/on chunks
	if( chunk_button->isChanged() )
	{
		music_button->turn();
		chunk_button->turn();
		git_button->turn();
		google_button->turn();
		play_button->turn();
		author_log->turn();
		game_log->turn();
		skill_log->turn();
		settings_log->turn();
		exit->turn();
		music_volume->turn();
		chunk_volume->turn();
		keyboard->turn();
		development->turn();
		headdeck->turn();
		reset_button->turn();
		sound.setChunkPlay( !sound.getChunkPlay() );
	}
	
	// Set music volume
	if( music_volume->isChanged() )
	{
		music->setVolume( music_volume->getVolume() );
		sound.setMusicVolume( music_volume->getVolume() );
	}
	
	// Set chunk volume
	if( chunk_volume->isChanged() )
	{
		music_button->setVolume( chunk_volume->getVolume() );
		chunk_button->setVolume( chunk_volume->getVolume() );
		git_button->setVolume( chunk_volume->getVolume() );
		google_button->setVolume( chunk_volume->getVolume() );
		play_button->setVolume( chunk_volume->getVolume() );
		author_log->setVolume( chunk_volume->getVolume() );
		game_log->setVolume( chunk_volume->getVolume() );
		skill_log->setVolume( chunk_volume->getVolume() );
		settings_log->setVolume( chunk_volume->getVolume() );
		exit->setVolume( chunk_volume->getVolume() );
		music_volume->setVolume( chunk_volume->getVolume() );
		chunk_volume->setVolume( chunk_volume->getVolume() );
		keyboard->setVolume( chunk_volume->getVolume() );
		development->setVolume( chunk_volume->getVolume() );
		headdeck->setVolume( chunk_volume->getVolume() );
		reset_button->setVolume( chunk_volume->getVolume() );
		sound.setChunkVolume( chunk_volume->getVolume() );
	}
	
	
		
	
	// Fade in
	if( play_button->getState() != 2 && exit->getState() == 0 && reset_button->getState() == 0 )// if user didn't click play
	{
		music->fadein( 1, music_volume->getVolume() );
		sf::Uint8 value = 2;
		git_button->fadein( value );
		google_button->fadein( value );
		twitter_button->fadein( value );
		facebook_button->fadein( value );
		scores_button->fadein( value );
		play_button->fadein( value );
		title->fadein( value );
		music_button->fadein( value );
		chunk_button->fadein( value );
		author_log->fadein( value );
		game_log->fadein( value );
		settings_log->fadein( value );
		music_volume->fadein( value );
		chunk_volume->fadein( value );
		skill_log->fadein( value );
		keyboard->fadein( value );
		information->fadein( value );
		development->fadein( value );
		headdeck->fadein( value );
		reset_button->fadein( value );
		nick->fadein( value );
		author->fadein( value );
	}
	
	// Fade out:
	else if( play_button->getState() == 2 ) // if user clicked play
	{
		music->fadeout( 1 );
		sf::Uint8 value = 3;
		git_button->fadeout( value );
		google_button->fadeout( value );
		twitter_button->fadeout( value );
		facebook_button->fadeout( value );
		scores_button->fadeout( value );
		play_button->fadeout( value );
		title->fadeout( value );
		music_button->fadeout( value );
		chunk_button->fadeout( value );
		author_log->fadeout( value );
		game_log->fadeout( value );
		settings_log->fadeout( value );
		music_volume->fadeout( value );
		chunk_volume->fadeout( value );
		skill_log->fadeout( value );
		keyboard->fadeout( value );
		information->fadeout( value );
		development->fadeout( value );
		headdeck->fadeout( value );
		reset_button->fadeout( value );
		nick->fadeout( value );
		author->fadeout( value );
	}
	else if( exit->getState() == 1 || reset_button->getState() == 1 ) // if user clicked exit
	{
		music->fadeout( 3, 20 );
		int value = 2, alpha = 170;
		git_button->fadeout( value, alpha );
		google_button->fadeout( value, alpha );
		twitter_button->fadeout( value, alpha );
		facebook_button->fadeout( value, alpha );
		scores_button->fadeout( value, alpha );
		play_button->fadeout( value, alpha );
		title->fadeout( value, alpha );
		music_button->fadeout( value, alpha );
		chunk_button->fadeout( value, alpha );
		author_log->fadeout( value, alpha );
		game_log->fadeout( value, alpha );
		settings_log->fadeout( value, alpha );
		music_volume->fadeout( value, alpha );
		chunk_volume->fadeout( value, alpha );
		skill_log->fadeout( value, alpha );
		keyboard->fadeout( value, alpha );
		information->fadeout( value, alpha );
		development->fadeout( value, alpha );
		headdeck->fadeout( value, alpha );
		reset_button->fadeout( value, alpha );
		nick->fadeout( value, alpha );
		author->fadeout( value, alpha );
	}
	else
	{
		int value = 3;
		music->fadeout( value );
		git_button->fadeout( value );
		google_button->fadeout( value );
		twitter_button->fadeout( value );
		facebook_button->fadeout( value );
		scores_button->fadeout( value );
		play_button->fadeout( value );
		title->fadeout( value );
		music_button->fadeout( value );
		chunk_button->fadeout( value );
		author_log->fadeout( value );
		game_log->fadeout( value );
		settings_log->fadeout( value );
		music_volume->fadeout( value );
		chunk_volume->fadeout( value );
		skill_log->fadeout( value );
		keyboard->fadeout( value );
		information->fadeout( value );
		development->fadeout( value );
		headdeck->fadeout( value );
		reset_button->fadeout( value );
		nick->fadeout( value );
		author->fadeout( value );
		
		if( title->getAlpha() == 0 )
		{
			state = 1;
		}
	}
	
	
	

	
	// Next state
	if( play_button->nextState() )
	{
		music->halt();
		play_button->setState( 0 );
		state = 2;
	}
		
	
	
	
	
	// Draw
	title->draw( *window );
	
	if( !author_log->getState() &&
		!game_log->getState() &&
		!skill_log->getState() &&
		!settings_log->getState() ) // if user didn't click logs
	{
		git_button->draw( *window );
		google_button->draw( *window );
		twitter_button->draw( *window );
		facebook_button->draw( *window );
		play_button->draw( window );
		music_button->draw( window );
		chunk_button->draw( window );
		reset_button->drawButton( window );
		scores_button->draw( *window );
		nick->draw( *window );
		nick->drawInfo( *window );
	}
	
	if( !author_log->getState() && !settings_log->getState() && !game_log->getState() )
	{
		skill_log->draw( window );
	}
	if( !skill_log->getState() && !author_log->getState() && !game_log->getState() )
	{
		settings_log->draw( window );
	}
	if( !skill_log->getState() && !settings_log->getState() && !author_log->getState() )
	{
		game_log->draw( window );
	}
	if( !skill_log->getState() && !settings_log->getState() && !game_log->getState() )
	{
		author_log->draw( window );
	}
	
		
			
	if( settings_log->getState() )
	{
		music_volume->draw( window );
		chunk_volume->draw( window );
		keyboard->draw( *window );
		information->draw( *window );
	}
	
	if( skill_log->getState() )
	{
		development->draw( window );
	}
	
	if( author_log->getState() )
	{
		headdeck->draw( window );
	}
	
	if( game_log->getState() )
	{
		author->draw( window );
	}
	else
	{
		author->reset();
	}
			
		
	if( exit->getState() < 2 )
	{
		exit->draw( window );
	}
	
	reset_button->draw( window );
	
	if( reset_button->doReset() )
	{
		development->reloadTxt();
		headdeck->reloadText();
		nick->setNick();
	}
	
	if( development->isChange() )
	{
		headdeck->setWallet( development->getWallet() );
	}
	else if( headdeck->isChange() )
	{
		development->setWallet( headdeck->getWallet() );
	}
=======
void Menu::load( float screen_w, float screen_h )
{
	free();
	
	float scale_x = screen_w /2560;
	float scale_y = screen_h /1440;
	
	// Load background.
	background.setIdentity( "menu-background" );
	background.load( "images/menu/background.png" );
	background.setScale( scale_x, scale_y );
	
	// Load "knight specs".
	knight_specs.load( screen_w, screen_h );
	
	// Load link buttons.
	github.load( screen_w /256, screen_h /144, "images/menu/github.png" );
	github.setScale( scale_x, scale_y );
	github.setUrl( "https://github.com/Adriqun/Combat-Halloween" );
	scores.load( github.getRight() +screen_w /256, screen_h /144, "images/menu/scores.png" );
	scores.setScale( scale_x, scale_y );
	scores.setUrl( "scores" );
	website.load( scores.getRight() +screen_w /256, screen_h /144, "images/menu/website.png" );
	website.setScale( scale_x, scale_y );
	website.setUrl( "http://adrianmichalek.pl/combathalloween/" );
	
	// Main buttons.
	singleplayer.load( screen_w /1.9, screen_h /2.35, "images/menu/singleplayer.png" );
	singleplayer.setScale( scale_x, scale_y );
	multiplayer.load( screen_w /1.9, singleplayer.getBot() +screen_h /72, "images/menu/multiplayer.png", true );
	multiplayer.setScale( scale_x, scale_y );
	exit.load( screen_w /1.9, multiplayer.getBot() +screen_h /72, "images/menu/exit.png" );
	exit.setScale( scale_x, scale_y );
	
	// Circle buttons.
	chunkbutton.load( "images/menu/chunk.png" );
	chunkbutton.setPosition( screen_w -screen_w /256, screen_h -screen_h /144, scale_x, scale_y );
	musicbutton.load( "images/menu/music.png" );
	musicbutton.setPosition( chunkbutton.getLeft() -screen_w /256, screen_h -screen_h /144, scale_x, scale_y );
	updatebutton.load( "images/level/update.png" );
	updatebutton.setPosition( website.getRight() +chunkbutton.getWidth() +screen_w /256, screen_h /144 +chunkbutton.getHeight(), scale_x, scale_y );
	reloadbutton.load( "images/menu/reload.png" );
	reloadbutton.setPosition( singleplayer.getLeft() -screen_w /256, singleplayer.getTop() +musicbutton.getHeight() +screen_h /72, scale_x, scale_y );
	settingsbutton.load( "images/menu/settings.png" );
	settingsbutton.setPosition( musicbutton.getLeft() -screen_w /256, screen_h -screen_h /144, scale_x, scale_y );
	
	// Settings.
	settings.load( screen_w, screen_h );
	
	// Set volume buttons.
	chunk_volume.load( chunkbutton.getLeft(), chunkbutton.getRight(), chunkbutton.getBot(), screen_w, screen_h );
	music_volume.load( musicbutton.getLeft(), musicbutton.getRight(), musicbutton.getBot(), screen_w, screen_h );
	
	// Load information.
	information.load( screen_w, screen_h );
	
	// Set chat.
	chat.load( screen_w, screen_h );
	chat.setCommandColor( sf::Color( 0, 0, 0 ) );
	chat.setTypicalColor( sf::Color( 0x68, 0x68, 0x68 ) );
	
	// Pause system.
	pausesystem.load( screen_w, screen_h );
	
	// Music.
	music.setIdentity( "menu-music" );
	music.load( "music/menu.ogg" );
}

void Menu::handle( sf::Event& event )
{
	if( !close && !ready && !editor )
	{
		if( !pausesystem.isActive() && pausesystem.getAlpha() == 0 )
		{
			chat.handle( event );
			
			if( !chat.isOpen() )
			{
				knight_specs.handle( event );
				github.handle( event );
				scores.handle( event );
				website.handle( event );
				singleplayer.handle( event );
				multiplayer.handle( event );
				exit.handle( event );
				
				if( !chunk_volume.handle( event ) )
				{
					chunkbutton.handle( event );
				}
				
				if( !music_volume.handle( event ) )
				{
					musicbutton.handle( event );
				}
				
				if( !knight_specs.isReady() || !information.isReady() )
				{
					reloadbutton.handle( event );
				}
				else
				{
					updatebutton.handle( event );
				}
				
				settingsbutton.handle( event );
				settings.handle( event );
			}
		}
		
		if( !chat.isOpen() )
		{
			pausesystem.handle( event );
		}
	}
}

void Menu::head( sf::RenderWindow* &window, double elapsedTime )
{
	mechanics( elapsedTime );
	fades( elapsedTime );
	draw( window );
}



void Menu::draw( sf::RenderWindow* &window )
{
	window->draw( background.get() );
	knight_specs.draw( window );
	github.draw( window );
	scores.draw( window );
	website.draw( window );
	singleplayer.draw( window );
	multiplayer.draw( window );
	exit.draw( window );
	chunkbutton.draw( window );
	musicbutton.draw( window );
	
	if( !knight_specs.isReady() || !information.isReady() )
	{
		reloadbutton.draw( window );
	}
	else
	{
		updatebutton.draw( window );
	}
	
	settingsbutton.draw( window );
	settings.draw( window );
	chunk_volume.draw( window );
	music_volume.draw( window );
	information.draw( window );
	chat.draw( window );
	pausesystem.draw( window );
}

void Menu::mechanics( double elapsedTime )
{
	// Mechanics.
	if( !pausesystem.isActive() && !close && !ready && !editor )
	{
		chat.mechanics( elapsedTime );
		if( chat.isCommand() )
		{
			// Knight specs.
			if( chat.findCommand( "@clear" ) )			knight_specs.setChosen( -1 );
			else if( chat.findCommand( "@helmet" ) )	knight_specs.setChosen( 0 );
			else if( chat.findCommand( "@body" ) )		knight_specs.setChosen( 1 );
			else if( chat.findCommand( "@shield" ) )	knight_specs.setChosen( 2 );
			else if( chat.findCommand( "@sword" ) )		knight_specs.setChosen( 3 );
			else if( chat.findCommand( "@boots" ) )		knight_specs.setChosen( 4 );
			
			// Close application.
			else if( chat.findCommand( "@close" ) || chat.findCommand( "@exit" ) )
			{
				exit.setPressed();
			}
			
			// Someone clicked singleplayer.
			else if( chat.findCommand( "@start" ) || chat.findCommand( "@play" ) )
			{
				if( knight_specs.isReady() && information.isReady() )
				{
					singleplayer.setPressed();
				}
			}
			
			// Exsert / shovel settings.
			else if( chat.findCommand( "@settings" ) || chat.findCommand( "@keyboard" ) ||
			chat.findCommand( "@keys" ) || chat.findCommand( "@sets" ) )
			{
				settingsbutton.setActive( !settingsbutton.isActive() );
			}
			
			// Reload data.
			else if( chat.findCommand( "@reload" ) || chat.findCommand( "@connect" ) ||
			chat.findCommand( "@rel" ) || chat.findCommand( "@con" ) )
			{
				reloadbutton.setActive( true );
			}
			
			// Update data.
			else if( chat.findCommand( "@update" ) )
			{
				updatebutton.setActive( true );
			}
			
			// Turn on/off all chunks.
			else if( chat.findCommand( "@chunk" ) )
			{
				chunkbutton.setChanged( true );
				chunkbutton.setActive( !chunkbutton.isActive() );
			}
			
			// Turn on/off music.
			else if( chat.findCommand( "@music" ) )
			{
				musicbutton.setChanged( true );
				musicbutton.setActive( !musicbutton.isActive() );
			}
			
			// Turn on/off all sounds.
			else if( chat.findCommand( "@sound" ) )
			{
				chunkbutton.setChanged( true );
				chunkbutton.setActive( !chunkbutton.isActive() );
				musicbutton.setChanged( true );
				musicbutton.setActive( !musicbutton.isActive() );
			}
			
			// Map editor.
			else if( chat.findCommand( "@editor" ) || chat.findCommand( "@edit" ) )
			{
				editor = true;
				chat.isOpen() = false;
			}
			
			// Link buttons in addition.
			else if( chat.findCommand( "@github" ) )		github.openWebsite();
			else if( chat.findCommand( "@scores" ) )		scores.openWebsite();
			else if( chat.findCommand( "@website" ) )	website.openWebsite();
			
			// Tell that command doesn't exist.
			else
			{
				chat.setError();
			}
		}
		
		// Knight specs
		knight_specs.mechanics( elapsedTime );
		
		
		// Close application.
		if( exit.isPressed() )
		{
			chat.isOpen() = false;
			close = true;
		}
		
		
		// Someone clicked singleplayer.
		if( singleplayer.isPressed() )
		{
			chat.isOpen() = false;
			ready = true;
		}
		
		
		// Exsert / shovel settings.
		if( settingsbutton.isActive() )
		{
			settings.exsertTable( elapsedTime );
		}
		else
		{
			settings.shovelTable( elapsedTime );
		}
		
		// if we dont have answer from database
		if( !knight_specs.isReady() || !information.isReady() )
		{
			singleplayer.lock();
		}
		else
		{
			singleplayer.unlock();
		}
		
		// update data
		if( updatebutton.isActive() )
		{
			updatebutton.setActive( false );
			
			if( knight_specs.isReady() && information.isReady() )
			{
				knight_specs.reloadValues();
				knight_specs.setThread();
				information.reloadMoney();
				information.setThread();
			}
		}
		
		// reload data
		if( reloadbutton.isActive() )
		{
			reloadbutton.setActive( false );
			if( !knight_specs.isReady() )
			{
				knight_specs.setThread();
			}
			
			if( !information.isReady() )
			{
				information.setThread();
			}
		}
		
		settings.mechanics( elapsedTime );
		chunk_volume.mechanics( elapsedTime );
		music_volume.mechanics( elapsedTime );
		
		// Turn on/off all chunks.
		if( chunkbutton.isChanged() )
		{
			github.setPlayable( chunkbutton.isActive() );
			scores.setPlayable( chunkbutton.isActive() );
			website.setPlayable( chunkbutton.isActive() );
			singleplayer.setPlayable( chunkbutton.isActive() );
			multiplayer.setPlayable( chunkbutton.isActive() );
			exit.setPlayable( chunkbutton.isActive() );
			chunkbutton.setPlayable( !chunkbutton.isActive() );
			musicbutton.setPlayable( chunkbutton.isActive() );
			settingsbutton.setPlayable( chunkbutton.isActive() );
			settings.setPlayable( chunkbutton.isActive() );
			chunk_volume.setPlayable( chunkbutton.isActive() );
			chunk_volume.setActive( chunkbutton.isActive() );
			music_volume.setPlayable( chunkbutton.isActive() );
			pausesystem.setPlayable( chunkbutton.isActive() );
		}
		
		// Volume of sounds is changed.
		if( chunk_volume.isChanged() )
		{
			float value = chunk_volume.getMainVolume();
			knight_specs.setVolume( value );
			github.setVolume( value );
			scores.setVolume( value );
			website.setVolume( value );
			singleplayer.setVolume( value );
			multiplayer.setVolume( value );
			exit.setVolume( value );
			chunkbutton.setVolume( value );
			musicbutton.setVolume( value );
			settingsbutton.setVolume( value );
			chunk_volume.setVolume( value );
			music_volume.setVolume( value );
			pausesystem.setVolume( value );
		}
		
		// Turn on/off music.
		if( musicbutton.isChanged() )
		{
			musicbutton.isActive() ? music.play() : music.pause();
			music_volume.setActive( musicbutton.isActive() );
		}
		
		// Volume of music is changed.
		if( music_volume.isChanged() )
		{
			music.setVolume( music_volume.getMainVolume() );
		}
	}
}

void Menu::fades( double elapsedTime )
{
	// Fade out - paused.
	if( pausesystem.isActive() )
	{
		float value = elapsedTime *0xFF *2;
		float min = 0xFF *3 /4;
		
		background.fadeout( value, min );
		knight_specs.fadeout( value, min );
		github.fadeout( value, min );
		scores.fadeout( value, min );
		website.fadeout( value, min );
		singleplayer.fadeout( value, min );
		multiplayer.fadeout( value, min );
		exit.fadeout( value, min );
		chunkbutton.fadeout( value, min );
		musicbutton.fadeout( value, min );
		updatebutton.fadeout( value, min );
		reloadbutton.fadeout( value, min );
		settingsbutton.fadeout( value, min );
		settings.fadeout( value, min );
		chunk_volume.fadeout( value, min );
		music_volume.fadeout( value, min );
		information.fadeout( value, min );
		chat.fadeout( value, min );
		pausesystem.fadein( value *3, min );
		
		music.fadeout( elapsedTime *100, music_volume.getMainVolume() *0.2 );
	}
	
	// Fade out - closed.
	else if( close || ready || editor )
	{
		float value = elapsedTime *0xFF;
		
		background.fadeout( value );
		knight_specs.fadeout( value );
		github.fadeout( value );
		scores.fadeout( value );
		website.fadeout( value );
		singleplayer.fadeout( value );
		multiplayer.fadeout( value );
		exit.fadeout( value );
		chunkbutton.fadeout( value );
		musicbutton.fadeout( value );
		updatebutton.fadeout( value );
		reloadbutton.fadeout( value );
		settingsbutton.fadeout( value );
		settings.fadeout( value );
		chunk_volume.fadeout( value );
		music_volume.fadeout( value );
		information.fadeout( value );
		chat.fadeout( value );
		
		music.fadeout( elapsedTime *100 );
	}
	
	// Fade in.
	else
	{
		float value = elapsedTime *0xFF *2;
		
		background.fadein( value );
		knight_specs.fadein( value );
		github.fadein( value );
		scores.fadein( value );
		website.fadein( value );
		singleplayer.fadein( value );
		multiplayer.fadein( value );
		exit.fadein( value );
		chunkbutton.fadein( value );
		musicbutton.fadein( value );
		updatebutton.fadein( value );
		reloadbutton.fadein( value );
		settingsbutton.fadein( value );
		settings.fadein( value );
		chunk_volume.fadein( value );
		music_volume.fadein( value );
		information.fadein( value );
		pausesystem.fadeout( value );
		
		music.fadein( elapsedTime *100, music_volume.getMainVolume() );
	}
}



void Menu::setUsername( string line )
{
	knight_specs.setUsername( line );
	information.setUsername( line );
	chat.setUsername( line );
}

void Menu::loadSound()
{
	if( !run )
	{
		run = true;
		
		// Set thread.
		knight_specs.setThread();
		information.setThread();
		
		float chunkVolume = 0;
		float musicVolume = 0;
		bool chunkPlay = false;
		bool musicPlay = false;
		
		MyFile file;
		file.load( "txt/sound.txt" );
		if( file.is_good() )
		{
			string line = "";
			file.get() >> line; chunkVolume = con::stof( line );
			file.get() >> line; musicVolume = con::stof( line );
			file.get() >> line; chunkPlay = con::stoi( line );
			file.get() >> line; musicPlay = con::stoi( line );
			
			// The rest.
			// printf( "%f %f %d %d\n", chunkVolume, musicVolume, chunkPlay, musicPlay );
			
			// Chunk.
			knight_specs.setVolume( chunkVolume );
			github.setVolume( chunkVolume );
			scores.setVolume( chunkVolume );
			website.setVolume( chunkVolume );
			singleplayer.setVolume( chunkVolume );
			multiplayer.setVolume( chunkVolume );
			exit.setVolume( chunkVolume );
			chunkbutton.setVolume( chunkVolume );
			musicbutton.setVolume( chunkVolume );
			updatebutton.setVolume( chunkVolume );
			reloadbutton.setVolume( chunkVolume );
			settingsbutton.setVolume( chunkVolume );
			settings.setVolume( chunkVolume );
			chunk_volume.setVolume( chunkVolume );
			chunk_volume.setMainVolume( chunkVolume );
			music_volume.setVolume( chunkVolume );
			pausesystem.setVolume( chunkVolume );
			
			// Music.
			music.setVolume( musicVolume );
			music_volume.setMainVolume( musicVolume );
			
			// Set playable.
			knight_specs.setPlayable( chunkPlay );
			github.setPlayable( chunkPlay );
			scores.setPlayable( chunkPlay );
			website.setPlayable( chunkPlay );
			singleplayer.setPlayable( chunkPlay );
			multiplayer.setPlayable( chunkPlay );
			exit.setPlayable( chunkPlay );
			chunkbutton.setPlayable( !chunkPlay );
			chunkbutton.setActive( chunkPlay );
			musicbutton.setPlayable( chunkPlay );
			musicbutton.setActive( musicPlay );
			updatebutton.setPlayable( chunkPlay );
			reloadbutton.setPlayable( chunkPlay );
			settingsbutton.setPlayable( chunkPlay );
			settings.setPlayable( chunkPlay );
			chunk_volume.setPlayable( chunkPlay );
			music_volume.setPlayable( chunkPlay );
			pausesystem.setPlayable( chunkPlay );
			musicPlay ? music.play() : music.pause();
		}
		
		file.free();
	}
}

void Menu::saveSound()
{
	MyFile file;
	file.load( "txt/sound.txt" );
	if( file.is_good() )
	{
		string line = con::itos( chunk_volume.getMainVolume() ); file.get() << line << endl;
		line = con::itos( music_volume.getMainVolume() ); file.get() << line << endl;
		line = con::itos( chunkbutton.isActive() ); file.get() << line << endl;
		line = con::itos( musicbutton.isActive() ); file.get() << line;
	}
	
	file.free();
	
	// plus
	ready = false;
	close = false;
	editor = false;
	run = false;
	
	// Reset.
	knight_specs.reload();
	singleplayer.reload();
	settingsbutton.setActive( false );
	settings.reload();
	chat.reset();
	music.stop();
>>>>>>> Combat-Halloween/master
}



<<<<<<< HEAD
bool Menu::isQuit()
{
	if( state == 1 )
=======
bool Menu::isReady()
{
	if( ready && background.getAlpha() == 0 )
>>>>>>> Combat-Halloween/master
	{
		return true;
	}
	
	return false;
}

<<<<<<< HEAD
bool Menu::nextState()
{
	if( state == 2 )
	{
		state = 0;
=======
bool Menu::isClose()
{
	if( close && background.getAlpha() == 0 )
	{
>>>>>>> Combat-Halloween/master
		return true;
	}
	
	return false;
}

<<<<<<< HEAD
void Menu::reloadMusic()
{
	if( sound.getMusicPlay() )
	{
		music_button->setState( 0 );
	}
	else
	{
		music_button->setState( 2 );
	}
	
	

	// Turn off/on chunks
	if( sound.getChunkPlay() )
	{
		chunk_button->setState( 0 );
		music_button->turnOn();
		chunk_button->turnOn();
		git_button->turnOn();
		google_button->turnOn();
		play_button->turnOn();
		author_log->turnOn();
		game_log->turnOn();
		skill_log->turnOn();
		settings_log->turnOn();
		exit->turnOn();
		music_volume->turnOn();
		chunk_volume->turnOn();
		keyboard->turnOn();
		development->turnOn();
		headdeck->turnOn();
		reset_button->turnOn();
	}
	else
	{
		chunk_button->setState( 2 );
		music_button->turnOff();
		chunk_button->turnOff();
		git_button->turnOff();
		google_button->turnOff();
		play_button->turnOff();
		author_log->turnOff();
		game_log->turnOff();
		skill_log->turnOff();
		settings_log->turnOff();
		exit->turnOff();
		music_volume->turnOff();
		chunk_volume->turnOff();
		keyboard->turnOff();
		development->turnOff();
		headdeck->turnOff();
		reset_button->turnOff();
	}
	
	music->reload();
	Mix_HaltMusic();
}

void Menu::checkMoney()
{
	development->reloadTxt();
	headdeck->reloadText();
}

void Menu::setNick()
{
	nick->setNick();
=======
bool Menu::isEditor()
{
	if( editor && background.getAlpha() == 0 )
	{
		return true;
	}
	
	return false;
>>>>>>> Combat-Halloween/master
}