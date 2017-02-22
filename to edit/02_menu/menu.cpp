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
	
	git_button = new Link_button( "https://github.com/Adriqun" );
	google_button = new Link_button( "https://en.wikipedia.org/wiki/Ninja" );
	twitter_button = new Link_button( "", true );
	facebook_button = new Link_button( "", true );
	

	background = new MySprite();
	background->setName( "menu-background" );
	
	play_button = new Play_button;
	
	author_log = new Log;
	game_log = new Log( true );
	settings_log = new Log();
	scores_log = new Log;
	
	exit = new Exit_log;
	
	music = new Music; music->setID( "menu-music" );
	
	version = new MyText;
	
	information = new Information;
	keyboard = new Keyboard;
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
	delete background;
	delete play_button;
	delete author_log;
	delete game_log;
	delete settings_log;
	delete scores_log;
	delete exit;
	delete music;
	delete version;
	delete information;
	delete keyboard;
}



void Menu::load( int screen_w, int screen_h )
{
	// title art
	title->load( screen_w );
	
	// sound buttons
	music_button->load( "data/sprites/menu/music.png", 10 );
	chunk_button->load( "data/sprites/menu/chunk.png", music_button->getBot() );
	
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
	git_button->load( "data/sprites/menu/git.png", screen_w );
	google_button->load( "data/sprites/menu/google.png", screen_w, git_button->getBot() );
	twitter_button->load( "data/sprites/menu/twitter.png", screen_w, google_button->getBot() );
	facebook_button->load( "data/sprites/menu/facebook.png", screen_w, twitter_button->getBot() );
	
	// bg
	background->load( "data/sprites/menu/background.png" );
	
	// button to start game
	play_button->load( screen_w, 400 );
	
	// logs
	author_log->load( "author", play_button->getX() +5, play_button->getBot() );
	game_log->load( "game", author_log->getRight(), play_button->getBot() );
	settings_log->load( "settings", game_log->getRight(), play_button->getBot() );
	scores_log->load( "scores", settings_log->getRight(), play_button->getBot() );
	
	// exit log
	exit->load( screen_w, screen_h );
	
	// music for menu
	music->load( "data/music/Rayman Legends OST - Moving Ground.mp3", 50 );
	
	// simple text on the right
	version->setName( "menu-version-text" );
	version->setFont( "data/fonts/BADABB__.TTF", 20, 0xFF, 0xFF, 0xFF );
	version->setText( "latest edition 22.02.2017" );
	version->setPosition( screen_w - version->getWidth() - 3, screen_h - version->getHeight() -7 );
	
	// information (keyboard) and keyboard
	information->load( music_volume->getRight(), screen_h/2 - 100, screen_h );
	keyboard->load( 100, music_volume->getRight(), screen_h/2 + 100, screen_w, screen_h );
	
	
	//Set start volume
	music_button->setVolume( chunk_volume->getVolume() );
	chunk_button->setVolume( chunk_volume->getVolume() );
	music_volume->setVolume( chunk_volume->getVolume() );
	chunk_volume->setVolume( chunk_volume->getVolume() );
	git_button->setVolume( chunk_volume->getVolume() );
	google_button->setVolume( chunk_volume->getVolume() );
	play_button->setVolume( chunk_volume->getVolume() );
	author_log->setVolume( chunk_volume->getVolume() );
	scores_log->setVolume( chunk_volume->getVolume() );
	settings_log->setVolume( chunk_volume->getVolume() );
	exit->setVolume( chunk_volume->getVolume() );
	keyboard->setVolume( chunk_volume->getVolume() );
}

void Menu::handle( sf::Event &event )
{
	if( play_button->getState() != 2 ) // if user didn't click play
	{
		exit->handle( event );
		if( exit->getState() == 0 ) // if user didn't click quit
		{
			if( !author_log->getState() && !scores_log->getState() && !settings_log->getState() ) // if user didn't click logs
			{
				git_button->handle( event );
				google_button->handle( event );
				twitter_button->handle( event );
				facebook_button->handle( event );
				play_button->handle( event );
				music_button->handle( event );
				chunk_button->handle( event );
			}
				
			if( !author_log->getState() && !settings_log->getState() )
			{
				scores_log->handle( event );
			}
			if( !scores_log->getState() && !settings_log->getState()  )
			{
				author_log->handle( event );
			}
			if( !scores_log->getState() && !author_log->getState()  )
			{
				settings_log->handle( event );
			}
				
				
			if( settings_log->getState() )
			{
				music_volume->handle( event );
				chunk_volume->handle( event );
				keyboard->handle( event );
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
		scores_log->turn();
		settings_log->turn();
		exit->turn();
		music_volume->turn();
		chunk_volume->turn();
		keyboard->turn(); 
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
		scores_log->setVolume( chunk_volume->getVolume() );
		settings_log->setVolume( chunk_volume->getVolume() );
		exit->setVolume( chunk_volume->getVolume() );
		music_volume->setVolume( chunk_volume->getVolume() );
		chunk_volume->setVolume( chunk_volume->getVolume() );
		keyboard->setVolume( chunk_volume->getVolume() );
		sound.setChunkVolume( chunk_volume->getVolume() );
	}
	
	
		
	
	// Fade in
	if( play_button->getState() != 2 && exit->getState() == 0 )// if user didn't click play
	{
		music->fadein( 1, music_volume->getVolume() );
		sf::Uint8 value = 2;
		background->fadein( value );
		git_button->fadein( value );
		google_button->fadein( value );
		twitter_button->fadein( value );
		facebook_button->fadein( value );
		play_button->fadein( value );
		title->fadein( value );
		music_button->fadein( value );
		chunk_button->fadein( value );
		author_log->fadein( value );
		game_log->fadein( value );
		settings_log->fadein( value );
		music_volume->fadein( value );
		chunk_volume->fadein( value );
		scores_log->fadein( value );
		version->fadein( value );
		keyboard->fadein( value );
		information->fadein( value );
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
		play_button->fadeout( value );
		title->fadeout( value );
		music_button->fadeout( value );
		chunk_button->fadeout( value );
		author_log->fadeout( value );
		game_log->fadeout( value );
		settings_log->fadeout( value );
		music_volume->fadeout( value );
		chunk_volume->fadeout( value );
		scores_log->fadeout( value );
		version->fadeout( value );
		keyboard->fadeout( value );
		information->fadeout( value );
	}
	else if( exit->getState() == 1 ) // if user clicked exit
	{
		music->fadeout( 3, 20 );
		int value = 2, alpha = 170;
		background->fadeout( value, alpha );
		git_button->fadeout( value, alpha );
		google_button->fadeout( value, alpha );
		twitter_button->fadeout( value, alpha );
		facebook_button->fadeout( value, alpha );
		play_button->fadeout( value, alpha );
		title->fadeout( value, alpha );
		music_button->fadeout( value, alpha );
		chunk_button->fadeout( value, alpha );
		author_log->fadeout( value, alpha );
		game_log->fadeout( value, alpha );
		settings_log->fadeout( value, alpha );
		music_volume->fadeout( value, alpha );
		chunk_volume->fadeout( value, alpha );
		scores_log->fadeout( value, alpha );
		version->fadeout( value, alpha );
		keyboard->fadeout( value, alpha );
		information->fadeout( value, alpha );
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
		play_button->fadeout( value );
		title->fadeout( value );
		music_button->fadeout( value );
		chunk_button->fadeout( value );
		author_log->fadeout( value );
		game_log->fadeout( value );
		settings_log->fadeout( value );
		music_volume->fadeout( value );
		chunk_volume->fadeout( value );
		scores_log->fadeout( value );
		version->fadeout( value );
		keyboard->fadeout( value );
		information->fadeout( value );
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
	window->draw( version->get() );
	
	if( !author_log->getState() && !scores_log->getState() && !settings_log->getState() ) // if user didn't click logs
	{
		git_button->draw( *window );
		google_button->draw( *window );
		twitter_button->draw( *window );
		facebook_button->draw( *window );
		play_button->draw( window );
		music_button->draw( window );
		chunk_button->draw( window );
		game_log->draw( window );
	}
	
	if( !author_log->getState() && !settings_log->getState() )
	{
		scores_log->draw( window );
	}
	if( !scores_log->getState() && !settings_log->getState() )
	{
		author_log->draw( window );
	}
	if( !scores_log->getState() && !author_log->getState() )
	{
		settings_log->draw( window );
	}
		
			
	if( settings_log->getState() )
	{
		music_volume->draw( window );
		chunk_volume->draw( window );
		keyboard->draw( *window );
		information->draw( *window );
	}
			
		
	if( exit->getState() < 2 )
	{
		exit->draw( window );
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
	music->reload();
	Mix_HaltMusic();
}