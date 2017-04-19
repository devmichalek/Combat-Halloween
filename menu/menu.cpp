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
	
	git_button = new Link_button( "https://github.com/Adriqun/Ninja" );
	google_button = new Link_button( "http://ninja2d.netne.net/" );
	twitter_button = new Link_button( "", true );
	facebook_button = new Link_button( "", true );
	scores_button = new Link_button( "http://ninja2d.netne.net/", true );
	

	background = new MySprite();
	background->setName( "menu-background" );
	
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
}

Menu::~Menu()
{
	free();
}

void Menu::free()
{
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
	delete background;
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
}



void Menu::load( int screen_w, int screen_h )
{
	// title art
	title->load( screen_w );
	
	// sound buttons
	music_button->load( "data/02_menu/music.png", 10, screen_w );
	music_button->setExplanator( "Turn on/off music.", screen_w );
	chunk_button->load( "data/02_menu/chunk.png", music_button->getBot(), screen_w );
	chunk_button->setExplanator( "Turn on/off chunks.", screen_w );
	
	// volume buttons
	music_volume->load( 100, screen_h/2 - 100, "Music" );
	chunk_volume->load( 100, music_volume->getBot() + 25, "Sound" );
	
	// chunk volume
	sound.setChunkPlay( true );
	sound.setChunkVolume( chunk_volume->getVolume() );
	
	// music volume
	sound.setMusicPlay( true );
	sound.setMusicVolume( music_volume->getVolume() );
	
	// link buttons
	git_button->load( "data/02_menu/git.png", screen_w, 10 );
	git_button->setExplanator( "Visit github!", screen_w );
	google_button->load( "data/02_menu/google.png", screen_w, git_button->getBot() );
	google_button->setExplanator( "Visit ninja2d.netne.net!", screen_w );
	twitter_button->load( "data/02_menu/twitter.png", screen_w, google_button->getBot() );
	twitter_button->setExplanator( "Twitter? Not today...", screen_w );
	facebook_button->load( "data/02_menu/facebook.png", screen_w, twitter_button->getBot() );
	facebook_button->setExplanator( "Damm, who needs facebook?", screen_w );
	scores_button->load( "data/02_menu/scores.png", facebook_button->getWidth() +20, screen_h -facebook_button->getHeight() -10 );
	scores_button->setExplanator( "Sorry dude, it's not ready", screen_w );
	
	// bg
	background->load( "data/02_menu/background.png" );
	
	// button to start game
	play_button->load( screen_w, 400 );
	
	// logs
	author_log->load( "author", play_button->getX() +9, play_button->getBot() );
	author_log->setExplanator( "Champions", screen_w );
	game_log->load( "game", author_log->getRight() -5, play_button->getBot() );
	game_log->setExplanator( "More games.", screen_w );
	settings_log->load( "settings", game_log->getRight(), play_button->getBot() );
	settings_log->setExplanator( "Go to the settings.", screen_w );
	skill_log->load( "skill", settings_log->getRight() -4, play_button->getBot() );
	skill_log->setExplanator( "Manage skills.", screen_w );
	
	// exit log
	exit->load( screen_w, screen_h );
	
	// music for menu
	music->load( "data/02_menu/music.mp3", 50 );
	
	// information (keyboard) and keyboard
	information->load( music_volume->getRight(), screen_h/2 - 100, screen_w, screen_h );
	keyboard->load( 100, music_volume->getRight(), screen_h/2 + 100, screen_w, screen_h );
	
	development->load( title->getBot() +140, screen_h );
	headdeck->load( title->getBot() +110, screen_h );
	
	reset_button->load( screen_w, screen_h );
	
	nick->load( screen_w, screen_h );
	author->load( screen_w, screen_h );
	
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
				scores_button->handle( event );
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
				settings_log->handle( event );
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
		background->fadein( value );
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
		background->fadeout( value );
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
		background->fadeout( value, alpha );
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
		background->fadeout( value );
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
		
		if( background->getAlpha() == 0 )
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
	window->draw( background->get() );
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
}



bool Menu::isQuit()
{
	if( state == 1 )
	{
		return true;
	}
	
	return false;
}

bool Menu::nextState()
{
	if( state == 2 )
	{
		state = 0;
		return true;
	}
	
	return false;
}

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
}