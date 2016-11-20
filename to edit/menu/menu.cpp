#include "menu.h"

Menu::Menu()
{
	// Create menu objects
	git_button = new Link_button( "https://github.com/Adriqun" );
	google_button = new Link_button( "https://en.wikipedia.org/wiki/Ninja" );
	twitter_button = new Link_button( "empty", true );
	facebook_button = new Link_button( "empty", true );
	background = new MySprite();	background->setName( "engine-background" );
	play_button = new Play_button;
	title = new Title;
	music_button = new Music_button;
	chunk_button = new Music_button( false );
	author_log = new Log;
	game_log = new Log( true );
	settings_log = new Log( false, false );
	scores_log = new Log;
	exit = new Exit_log;
	music = new Music; music->setID( "engine-music" );
	music_volume = new Music_volume( 64 );
	chunk_volume = new Music_volume( 51.2 );
	keyboard = new Keyboard;
	version = new MyText;
	setkeyboard = new Setkeyboard;
	information = new Information;
	state = new State( 0, true, true, 0, 0 );
}

Menu::~Menu()
{
	free();
}

void Menu::free()
{
	delete git_button;
	delete google_button;
	delete twitter_button;
	delete facebook_button;
	delete background;
	delete play_button;
	delete title;
	delete music_button;
	delete chunk_button;
	delete author_log;
	delete game_log;
	delete settings_log;
	delete scores_log;
	delete exit;
	delete music;
	delete music_volume;
	delete chunk_volume;
	delete keyboard;
	delete version;
	delete setkeyboard;
	delete information;
	delete state;
}

	
	
void Menu::load( int screen_width, int screen_height )
{
	git_button->load( "data/sprites/menu/git.png", screen_width );
	google_button->load( "data/sprites/menu/google.png", screen_width, git_button->getBot() );
	twitter_button->load( "data/sprites/menu/twitter.png", screen_width, google_button->getBot() );
	facebook_button->load( "data/sprites/menu/facebook.png", screen_width, twitter_button->getBot() );
	
	background->load( "data/sprites/menu/background.png" );
	
	play_button->load( screen_width, 400 );
	
	title->load( screen_width );
	
	music_button->load( "data/sprites/menu/music.png", 10 );
	chunk_button->load( "data/sprites/menu/chunk.png", music_button->getBot() );
	
	author_log->load( "author", play_button->getX() +5, play_button->getBot() +10, screen_width );
	game_log->load( "game", author_log->getRight(), play_button->getBot() +10, screen_width );
	settings_log->load( "settings", game_log->getRight(), play_button->getBot() +10, screen_width );
	scores_log->load( "scores", settings_log->getRight(), play_button->getBot() +10, screen_width );
	
	exit->load( screen_width, screen_height );
	
	music->load( "data/music/Rayman Legends OST - Moving Ground.mp3", 50 );
	
	music_volume->load( 100, screen_height/2 - 100, "Music" );
	chunk_volume->load( 100, music_volume->getBot() + 25, "Sound" );
	
	keyboard->load( music_volume->getRight(), screen_height/2 - 100 );
	
	version->setID( "menu-version-text" );
	version->setFont( "data/fonts/BADABB__.TTF", 20, 0xFF, 0xFF, 0xFF );
	version->setText( "latest edition 20.11.2016" );
	version->setPosition( screen_width - version->getWidth() - 3, screen_height - version->getHeight() -7 );
	
	setkeyboard->load( 100, music_volume->getRight(), screen_height/2 + 100 );
	setkeyboard->loadButton( screen_width, screen_height );
	information->load( screen_height );
	
	//Set start volume
	git_button->setVolume( chunk_volume->getVolume() );
	google_button->setVolume( chunk_volume->getVolume() );
	music_button->setVolume( chunk_volume->getVolume() );
	chunk_button->setVolume( chunk_volume->getVolume() );
	play_button->setVolume( chunk_volume->getVolume() );
	author_log->setVolume( chunk_volume->getVolume() );
	scores_log->setVolume( chunk_volume->getVolume() );
	settings_log->setVolume( chunk_volume->getVolume() );
	exit->setVolume( chunk_volume->getVolume() );
	music_volume->setVolume( chunk_volume->getVolume() );
	chunk_volume->setVolume( chunk_volume->getVolume() );
	setkeyboard->setVolume( chunk_volume->getVolume() );
	
	state->cVolume = chunk_volume->getVolume();
	state->mVolume = music_volume->getVolume();
}


void Menu::handle( sf::Event &event )
{
	if( play_button->getState() != 2 ) // if user didn't click play
		{
			exit->handle( event );
			if( exit->getState() == 0 ) // if user didn't click quit
			{
				if( author_log->getState() != 2 && scores_log->getState() != 2 && settings_log->getState() != 2 ) // if user didn't click logs
				{
					git_button->handle( event );
					google_button->handle( event );
					twitter_button->handle( event );
					facebook_button->handle( event );
					play_button->handle( event );
					music_button->handle( event );
					chunk_button->handle( event );
				}
					
				if( author_log->getState() != 2 && settings_log->getState() != 2 )
					scores_log->handle( event );
				if( scores_log->getState() != 2 && settings_log->getState() != 2  )	
					author_log->handle( event );
				if( scores_log->getState() != 2 && author_log->getState() != 2  )	
					settings_log->handle( event );
					
				if( settings_log->getState() == 2 )
				{
					music_volume->handle( event );
					chunk_volume->handle( event );
					setkeyboard->handle( event );
				}
			}
		}
}

	
	
void Menu::draw( sf::RenderWindow* &window )
{
	if( state->mSwitch )
	{
		music->play();
	}
		
		
		
		
	// Turn off/on music
	if( music_button->change() )
	{
		music->pause();
		state->mSwitch = !state->mSwitch;
	}
	// Turn off/on chunks
	if( chunk_button->change() )
	{
		git_button->turn();
		google_button->turn();
		music_button->turn();
		chunk_button->turn();
		play_button->turn();
		author_log->turn();
		scores_log->turn();
		settings_log->turn();
		exit->turn();
		music_volume->turn();
		chunk_volume->turn();
		setkeyboard->turn(); 
		state->cSwitch = !state->cSwitch;
	}
	
	// Set music volume
	if( music_volume->changeVolume() )
	{
		music->setVolume( music_volume->getVolume() );
		state->mVolume = music_volume->getVolume();
	}
	
	// Set chunk volume
	if( chunk_volume->changeVolume() )
	{
		git_button->setVolume( chunk_volume->getVolume() );
		google_button->setVolume( chunk_volume->getVolume() );
		music_button->setVolume( chunk_volume->getVolume() );
		chunk_button->setVolume( chunk_volume->getVolume() );
		play_button->setVolume( chunk_volume->getVolume() );
		author_log->setVolume( chunk_volume->getVolume() );
		scores_log->setVolume( chunk_volume->getVolume() );
		settings_log->setVolume( chunk_volume->getVolume() );
		exit->setVolume( chunk_volume->getVolume() );
		music_volume->setVolume( chunk_volume->getVolume() );
		chunk_volume->setVolume( chunk_volume->getVolume() );
		state->cVolume = chunk_volume->getVolume();
		setkeyboard->setVolume( chunk_volume->getVolume() );
	}
	
	
		
	
	// Fade in
	if( play_button->getState() != 2 && exit->getState() == 0 )// if user didn't click play
	{
		music->fadein( 1, music_volume->getVolume() );
		background->fadein( 2, 255 );
		git_button->fadein( 2, 255 );
		google_button->fadein( 2, 255 );
		twitter_button->fadein( 2, 255 );
		facebook_button->fadein( 2, 255 );
		play_button->fadein( 2 );
		title->fadein( 2 );
		music_button->fadein( 2, 255 );
		chunk_button->fadein( 2, 255 );
		author_log->fadein( 2 );
		game_log->fadein( 2 );
		settings_log->fadein( 2, 255 );
		music_volume->fadein( 2, 255 );
		chunk_volume->fadein( 2, 255 );
		scores_log->fadein( 2, 255 );
		keyboard->fadein( 2, 255 );
		version->fadein( 2, 255 );
		setkeyboard->fadein( 2, 255 );
		information->fadein( 2, 255 );
	}
	// Fade out:
	else if( play_button->getState() == 2 ) // if user clicked play
	{
		music->fadeout( 1, 0 );
		background->fadeout( 3, 0 );
		git_button->fadeout( 3, 0 );
		google_button->fadeout( 3, 0 );
		twitter_button->fadeout( 3, 0 );
		facebook_button->fadeout( 3, 0 );
		play_button->fadeout( 3 );
		title->fadeout( 3 );
		music_button->fadeout( 3, 0 );
		chunk_button->fadeout( 3, 0 );
		author_log->fadeout( 3 );
		game_log->fadeout( 3 );
		settings_log->fadeout( 3, 0 );
		music_volume->fadeout( 3, 0 );
		chunk_volume->fadeout( 3, 0 );
		scores_log->fadeout( 3, 0 );
		keyboard->fadeout( 3, 0 );
		version->fadeout( 3, 0 );
		setkeyboard->fadeout( 3, 0 );
		information->fadeout( 3, 0 );
	}
	else if( exit->getState() == 1 ) // if user clicked exit
	{
		music->fadeout( 3, 20 );
		background->fadeout( 2, 170 );
		git_button->fadeout( 2, 170 );
		google_button->fadeout( 2, 170 );
		twitter_button->fadeout( 2, 170 );
		facebook_button->fadeout( 2, 170 );
		play_button->fadeout( 2, 170 );
		title->fadeout( 2, 170 );
		music_button->fadeout( 2, 170 );
		chunk_button->fadeout( 2, 170 );
		author_log->fadeout( 2, 170 );
		game_log->fadeout( 2, 170 );
		settings_log->fadeout( 2, 170 );
		music_volume->fadeout( 2, 170 );
		chunk_volume->fadeout( 2, 170 );
		scores_log->fadeout( 2, 170 );
		keyboard->fadeout( 2, 170 );
		version->fadeout( 2, 170 );
		setkeyboard->fadeout( 2, 170 );
		information->fadeout( 2, 170 );
	}
	else
	{
		music->fadeout( 3, 0 );
		background->fadeout( 3, 0 );
		git_button->fadeout( 3, 0 );
		google_button->fadeout( 3, 0 );
		twitter_button->fadeout( 3, 0 );
		facebook_button->fadeout( 3, 0 );
		play_button->fadeout( 3 );
		title->fadeout( 3 );
		music_button->fadeout( 3, 0 );
		chunk_button->fadeout( 3, 0 );
		author_log->fadeout( 3 );
		game_log->fadeout( 3 );
		settings_log->fadeout( 3, 0 );
		music_volume->fadeout( 3, 0 );
		chunk_volume->fadeout( 3, 0 );
		scores_log->fadeout( 3, 0 );
		keyboard->fadeout( 3, 0 );
		version->fadeout( 3, 0 );
		setkeyboard->fadeout( 3, 0 );
		information->fadeout( 3, 0 );
		if( background->getAlpha() == 0 )
		{
			state->state = 1;
		}
	}
	
	
	

	
	// Next state
	if( play_button->nextGameState() )
	{
		music->halt();
		play_button->setState( 0 );
		state->state = 2;
	}
		
	
	
	
	
	// Draw
	window->draw( background->get() );
	title->draw( *window );
	window->draw( version->get() );
	
	if( author_log->getState() != 2 && scores_log->getState() != 2 && settings_log->getState() != 2 ) // if user didn't click logs
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
	
	if( author_log->getState() != 2 && settings_log->getState() != 2 )
		scores_log->draw( window );
	if( scores_log->getState() != 2 && settings_log->getState() != 2 )
		author_log->draw( window );
	if( scores_log->getState() != 2 && author_log->getState() != 2 )
		settings_log->draw( window );
			
	if( settings_log->getState() == 2 )
	{
		music_volume->draw( window );
		chunk_volume->draw( window );
		keyboard->draw( *window );
		setkeyboard->draw( *window );
		information->draw( *window );
	}
			
		
	if( exit->getState() < 2 )
		exit->draw( window );
}

bool Menu::isQuit()
{
	if( state->state == 1 )
	{
		return true;
	}
	
	return false;
}

bool Menu::nextState()
{
	if( state->state == 2 )
	{
		state->state = 0;
		return true;
	}
	
	return false;
}

State* Menu::getState()
{
	return state;
}

void Menu::reloadMusic()
{
	music->reload();
}