#include "engine.h"
#include <stdio.h>

// Create objects.
Engine::Engine()
{
	// Create and load core object
    core = new Core( -2, 1024, 768 );
    core->load( "Ninja" );
	
	// Create and load loading object
	loading = new Loading;
	loading->load( core->getWidth(), core->getHeight() );
	
	// Create intro object
	intro = new Intro;
	
	// Create menu objects
	git_button = new Link_button( "https://github.com/Adriqun" );
	google_button = new Link_button( "https://en.wikipedia.org/wiki/Ninja" );
	twitter_button = new Link_button( "empty", true );
	facebook_button = new Link_button( "empty", true );
	menu_background = new MySprite;	menu_background->setID( "engine-menu_background" );
	menu_play_button = new Menu_play_button;
	menu_title = new Menu_title;
	menu_music_button = new Menu_music_button;
	menu_chunk_button = new Menu_music_button( false );
	author_log = new Menu_log;
	game_log = new Menu_log( true );
	settings_log = new Menu_log( false, false );
	scores_log = new Menu_log;
	menu_exit = new Menu_exit_log;
	menu_music = new Music; menu_music->setID( "engine-menu_music" );
	music_volume = new Music_volume;
	
	// Create play objects
	game_timer = new Game_timer;
}


// Free objects.
void Engine::free()
{	
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
	
	delete game_timer;
	
	delete core;
}


// Load objects.
void Engine::load()
{
	loading->draw( core->getWindow(), 99 );
	
	switch( loading->getState() )
	{
		case 0:
		menu_music->load( "menu/Rayman Legends OST - Moving Ground.mp3" );
		break;
		
		case 1:
		git_button->load( "menu/git.png", core->getWidth() );
		google_button->load( "menu/google.png", core->getWidth(), git_button->getBot() );
		twitter_button->load( "menu/twitter.png", core->getWidth(), google_button->getBot() );
		facebook_button->load( "menu/facebook.png", core->getWidth(), twitter_button->getBot() );
		break;
		
		case 2:
		menu_background->load( "menu/background.png" );
		break;
		
		case 3:
		menu_play_button->load( core->getWidth(), 400 );
		break;
		
		case 4:
		menu_title->load( core->getWidth() );
		break;
		
		case 5:
		menu_music_button->load( "menu/music.png", 10 );
		menu_chunk_button->load( "menu/chunk.png", menu_music_button->getBot() );
		break;
		
		case 6:
		author_log->load( "author", menu_play_button->getX() +5, menu_play_button->getBot() +10, core->getWidth() );
		game_log->load( "game", author_log->getRight(), menu_play_button->getBot() +10, core->getWidth() );
		settings_log->load( "settings", game_log->getRight(), menu_play_button->getBot() +10, core->getWidth() );
		scores_log->load( "scores", settings_log->getRight(), menu_play_button->getBot() +10, core->getWidth() );
		break;
		
		case 7:
		menu_exit->load( core->getWidth(), core->getHeight() );
		break;
		
		case 8:
		menu_music->load( "menu/Rayman Legends OST - Moving Ground.mp3", 50 );
		break;
		
		case 9:
		intro->load( core->getWidth(), core->getHeight() );
		break;
		
		case 10:
		game_timer->load( core->getWidth() );
		break;
		
		case 11:
		music_volume->load( core->getWidth(), core->getHeight(), "Music" );
		break;
		
		
		case 100:
		delete loading;
		core->getState() = -1;	// intro state
		break;
			
	}
}


// Control objects.
void Engine::events()
{
    while( core->getWindow()->pollEvent( core->getEvent() ) )
    {
        if( core->getEvent().type == sf::Event::Closed )
        {
            core->isOpen() = false;
        }
		
/////////////////////////////////////////////////////////////////////////////////////

        if( core->getState() == 0 ) // if we actually have menu state
        {
			if( menu_play_button->getState() != 2 ) // if user didn't click play
			{
				menu_exit->handle( core->getEvent() );
				if( menu_exit->getState() == 0 ) // if user didn't click quit
				{
					if( author_log->getState() != 2 && scores_log->getState() != 2 ) // if user didn't click logs
					{
						git_button->handle( core->getEvent() );
						google_button->handle( core->getEvent() );
						twitter_button->handle( core->getEvent() );
						facebook_button->handle( core->getEvent() );
						menu_play_button->handle( core->getEvent() );
						menu_music_button->handle( core->getEvent() );
						menu_chunk_button->handle( core->getEvent() );
					}
					
					if( author_log->getState() != 2 && settings_log->getState() != 2 )
						scores_log->handle( core->getEvent() );
					if( scores_log->getState() != 2 && settings_log->getState() != 2  )	
						author_log->handle( core->getEvent() );
					if( scores_log->getState() != 2 && author_log->getState() != 2  )	
						settings_log->handle( core->getEvent() );
				}
			}
        }
		
/////////////////////////////////////////////////////////////////////////////////////
		
		if( core->getState() == 1 ) // if we actually have play state
		{
			game_timer->handle( core->getEvent() );
		}

    }
}

// Render objects.
void Engine::states()
{
	if( core->getState() == -2 ) // loading state
	{
		load();
	}
	
	if( core->getState() == -1 ) // loading state
	{
		intro->draw( core->getWindow() );
		if( intro->isQuit() )
		{
			delete intro;
			core->getState() = 0;
		}
	}
	
    if( core->getState() == 0 ) // menu state
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
			scores_log->fadeout( 3, 0 );
			if( menu_background->getAlpha() == 0 )
				core->isOpen() = false;
		}
		
		// Next state
		if( menu_play_button->nextGameState() )
		{
			core->getState() = 1;
		}
		
		
		// Draw
		core->getWindow()->draw( menu_background->get() );
		menu_title->draw( *core->getWindow() );
		if( author_log->getState() != 2 && scores_log->getState() != 2 && settings_log->getState() != 2 ) // if user didn't click logs
		{
			git_button->draw( *core->getWindow() );
			google_button->draw( *core->getWindow() );
			twitter_button->draw( *core->getWindow() );
			facebook_button->draw( *core->getWindow() );
			menu_play_button->draw( core->getWindow() );
			menu_music_button->draw( core->getWindow() );
			menu_chunk_button->draw( core->getWindow() );
			game_log->draw( core->getWindow() );
		}
		if( author_log->getState() != 2 && settings_log->getState() != 2 )
			scores_log->draw( core->getWindow() );
		if( scores_log->getState() != 2 && settings_log->getState() != 2 )
			author_log->draw( core->getWindow() );
		if( scores_log->getState() != 2 && author_log->getState() != 2 )
			settings_log->draw( core->getWindow() );
		
		if( menu_exit->getState() < 2 )
			menu_exit->draw( core->getWindow() );
    }
	
	if( core->getState() == 1 ) // play state
    {
		game_timer->draw( *core->getWindow() );
		game_timer->count( core->getWidth() );
		game_timer->fadein( 3 );
	}
}







// We don't care about things below.
// They will look the same all time
void Engine::loop()
{
    while( core->isOpen() )
    {
        core->clear();

        events();
        states();

        core->display();
    }
}

// Delete engine equils delete objects
Engine::~Engine()
{
    free();
}
