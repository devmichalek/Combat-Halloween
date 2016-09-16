#include "menu.h"

Menu::Menu()
{
	width = height = 0;
	state = 0;
	
	// Create menu objects
	git_button = new Link_button( "https://github.com/Adriqun" );
	google_button = new Link_button( "https://en.wikipedia.org/wiki/Ninja" );
	twitter_button = new Link_button( "empty", true );
	facebook_button = new Link_button( "empty", true );
	menu_background = new MySprite();	menu_background->setName( "engine-menu_background" );
	menu_play_button = new Play_button;
	menu_title = new Title;
	menu_music_button = new Music_button;
	menu_chunk_button = new Music_button( false );
	author_log = new Log;
	game_log = new Log( true );
	settings_log = new Log( false, false );
	scores_log = new Log;
	menu_exit = new Exit_log;
	menu_music = new Music; menu_music->setID( "engine-menu_music" );
	music_volume = new Music_volume;
}

Menu::~Menu()
{
	free();
}

void Menu::free()
{
	width = height = 0;
	
	
	delete git_button;
	delete google_button;
	delete twitter_button;
	delete facebook_button;
	delete menu_background;
	delete menu_play_button;
	delete menu_title;
	delete menu_music_button;
	delete menu_chunk_button;
	delete author_log;
	delete game_log;
	delete settings_log;
	delete scores_log;
	delete menu_exit;
	delete menu_music;
	delete music_volume;
}

	
void Menu::load( int screen_width, int screen_height )
{
	width = screen_width;
	height = screen_height;
	
	git_button->load( "menu/git.png", screen_width );
	google_button->load( "menu/google.png", screen_width, git_button->getBot() );
	twitter_button->load( "menu/twitter.png", screen_width, google_button->getBot() );
	facebook_button->load( "menu/facebook.png", screen_width, twitter_button->getBot() );
	
	menu_background->load( "menu/background.png" );
	
	menu_play_button->load( screen_width, 400 );
	
	menu_title->load( screen_width );
	
	menu_music_button->load( "menu/music.png", 10 );
	menu_chunk_button->load( "menu/chunk.png", menu_music_button->getBot() );
	
	author_log->load( "author", menu_play_button->getX() +5, menu_play_button->getBot() +10, screen_width );
	game_log->load( "game", author_log->getRight(), menu_play_button->getBot() +10, screen_width );
	settings_log->load( "settings", game_log->getRight(), menu_play_button->getBot() +10, screen_width );
	scores_log->load( "scores", settings_log->getRight(), menu_play_button->getBot() +10, screen_width );
	
	menu_exit->load( screen_width, screen_height );
	
	menu_music->load( "menu/Rayman Legends OST - Moving Ground.mp3", 50 );
	
	music_volume->load( screen_width, screen_height, "Music" );
}


void Menu::handle( sf::Event &event )
{
	if( menu_play_button->getState() != 2 ) // if user didn't click play
		{
			menu_exit->handle( event );
			if( menu_exit->getState() == 0 ) // if user didn't click quit
			{
				if( author_log->getState() != 2 && scores_log->getState() != 2 && settings_log->getState() != 2 ) // if user didn't click logs
				{
					git_button->handle( event );
					google_button->handle( event );
					twitter_button->handle( event );
					facebook_button->handle( event );
					menu_play_button->handle( event );
					menu_music_button->handle( event );
					menu_chunk_button->handle( event );
				}
					
				if( author_log->getState() != 2 && settings_log->getState() != 2 )
					scores_log->handle( event );
				if( scores_log->getState() != 2 && settings_log->getState() != 2  )	
					author_log->handle( event );
				if( scores_log->getState() != 2 && author_log->getState() != 2  )	
					settings_log->handle( event );
			}
		}
}

	
void Menu::draw( sf::RenderWindow* &window )
{
	menu_music->play();
		
		
		
	// Turn off/on music
	if( menu_music_button->change() )
	{
		menu_music->pause();
	}
	// Turn off/on chunks
	if( menu_chunk_button->change() )
	{
		git_button->turn();
		google_button->turn();
		menu_music_button->turn();
		menu_chunk_button->turn();
		menu_play_button->turn();
		author_log->turn();
		scores_log->turn();
		settings_log->turn();
		menu_exit->turn();
	}
	
	
	
		
	
	// Fade in
	if( menu_play_button->getState() != 2 && menu_exit->getState() == 0 )// if user didn't click play
	{
		menu_music->fadein( 2, 40 );
		menu_background->fadein( 2, 255 );
		git_button->fadein( 2, 255 );
		google_button->fadein( 2, 255 );
		twitter_button->fadein( 2, 255 );
		facebook_button->fadein( 2, 255 );
		menu_play_button->fadein( 2, 255 );
		menu_title->fadein( 2, 255 );
		menu_music_button->fadein( 2, 255 );
		menu_chunk_button->fadein( 2, 255 );
		author_log->fadein( 2, 255 );
		game_log->fadein( 2, 255 );
		settings_log->fadein( 2, 255 );
		music_volume->fadein( 2, 255 );
		scores_log->fadein( 2, 255 );
	}
	// Fade out:
	else if( menu_play_button->getState() == 2 ) // if user clicked play
	{
		menu_music->fadeout( 1, 0 );
		menu_background->fadeout( 3, 0 );
		git_button->fadeout( 3, 0 );
		google_button->fadeout( 3, 0 );
		twitter_button->fadeout( 3, 0 );
		facebook_button->fadeout( 3, 0 );
		menu_play_button->fadeout( 3, 0 );
		menu_title->fadeout( 3, 0 );
		menu_music_button->fadeout( 3, 0 );
		menu_chunk_button->fadeout( 3, 0 );
		author_log->fadeout( 3, 0 );
		game_log->fadeout( 3, 0 );
		settings_log->fadeout( 3, 0 );
		music_volume->fadeout( 3, 0 );
		scores_log->fadeout( 3, 0 );
	}
	else if( menu_exit->getState() == 1 ) // if user clicked exit
	{
		menu_music->fadeout( 3, 20 );
		menu_background->fadeout( 2, 170 );
		git_button->fadeout( 2, 170 );
		google_button->fadeout( 2, 170 );
		twitter_button->fadeout( 2, 170 );
		facebook_button->fadeout( 2, 170 );
		menu_play_button->fadeout( 2, 170 );
		menu_title->fadeout( 2, 170 );
		menu_music_button->fadeout( 2, 170 );
		menu_chunk_button->fadeout( 2, 170 );
		author_log->fadeout( 2, 170 );
		game_log->fadeout( 2, 170 );
		settings_log->fadeout( 2, 170 );
		music_volume->fadeout( 2, 170 );
		scores_log->fadeout( 2, 170 );
	}
	else
	{
		menu_music->fadeout( 3, 0 );
		menu_background->fadeout( 3, 0 );
		git_button->fadeout( 3, 0 );
		google_button->fadeout( 3, 0 );
		twitter_button->fadeout( 3, 0 );
		facebook_button->fadeout( 3, 0 );
		menu_play_button->fadeout( 3, 0 );
		menu_title->fadeout( 3, 0 );
		menu_music_button->fadeout( 3, 0 );
		menu_chunk_button->fadeout( 3, 0 );
		author_log->fadeout( 3, 0 );
		game_log->fadeout( 3, 0 );
		settings_log->fadeout( 3, 0 );
		music_volume->fadeout( 3, 0 );
		scores_log->fadeout( 3, 0 );
		if( menu_background->getAlpha() == 0 )
			state = 1;
	}
	
	
	

	
	// Next state
	if( menu_play_button->nextGameState() )
	{
		state = 2;
	}
		
	
	
	
	
	// Draw
	window->draw( menu_background->get() );
	menu_title->draw( *window );
	
	if( author_log->getState() != 2 && scores_log->getState() != 2 && settings_log->getState() != 2 ) // if user didn't click logs
	{
		git_button->draw( *window );
		google_button->draw( *window );
		twitter_button->draw( *window );
		facebook_button->draw( *window );
		menu_play_button->draw( window );
		menu_music_button->draw( window );
		menu_chunk_button->draw( window );
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
	}
			
		
	if( menu_exit->getState() < 2 )
		menu_exit->draw( window );
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
		return true;
	}
	
	return false;
}
