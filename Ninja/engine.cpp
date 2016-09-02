#include "engine.h"
#include <stdio.h>

// Create objects.
Engine::Engine()
{
    core = new Core( 1024, 768 );
	
	git_button = new Link_button( "https://github.com/Adriqun" );
	google_button = new Link_button( "https://en.wikipedia.org/wiki/Ninja" );
	twitter_button = new Link_button( "empty", true );
	facebook_button = new Link_button( "empty", true );
	menu_background = new MySprite;
	menu_play_button = new Menu_play_button;
}


// Free objects.
void Engine::free()
{
    delete core;
	
	delete git_button;
	delete google_button;
	delete twitter_button;
	delete facebook_button;
	delete menu_background;
	delete menu_play_button;
}


// Load objects.
bool Engine::load()
{
    if( !core->load( "Ninja" ) ) return false;
	
	if( !git_button->load( "menu/git.png", core->getWidth() ) ) 									return false;
	if( !google_button->load( "menu/google.png", core->getWidth(), git_button->getBot() ) ) 		return false;
	if( !twitter_button->load( "menu/twitter.png", core->getWidth(), google_button->getBot() ) ) 	return false;
	if( !facebook_button->load( "menu/facebook.png", core->getWidth(), twitter_button->getBot() ) ) return false;
	if( !menu_background->load( "menu/background.png" ) )	return false;
	if( !menu_play_button->load( core->getWidth(), 400 ) )	return false;

    return true;
}


// Control objects.
void Engine::events()
{
    while( core->getWindow()->pollEvent( core->getEvent() ) )
    {
        if( core->getEvent().type == Event::Closed )
        {
            core->isOpen() = false;
        }

        if( core->getState() == 0 ) // if we actually have menu state
        {
			if( menu_play_button->getState() != 2 ) // if user didn't click play
			{
				git_button->handle( core->getEvent() );
				google_button->handle( core->getEvent() );
				twitter_button->handle( core->getEvent() );
				facebook_button->handle( core->getEvent() );
				menu_play_button->handle( core->getEvent() );
			}

			
        }

    }
}

// Render objects.
void Engine::states()
{
    if( core->getState() == 0 ) // menu state
    {
		// Fade in
		if( menu_play_button->getState() != 2 )// if user didn't click play
		{
			menu_background->fadein( 5, 255 );
			git_button->fadein( 5, 255 );
			google_button->fadein( 5, 255 );
			twitter_button->fadein( 5, 255 );
			facebook_button->fadein( 5, 255 );
			menu_play_button->fadein( 5, 255 );
		}
		
		
		// Fade out:
		else if( menu_play_button->getState() == 2 ) // if user clicked play
		{
			menu_background->fadeout( 5, 0 );
			git_button->fadeout( 5, 0 );
			google_button->fadeout( 5, 0 );
			twitter_button->fadeout( 5, 0 );
			facebook_button->fadeout( 5, 0 );
			menu_play_button->fadeout( 5, 0 );
		}
		
		// Next state
		if( menu_play_button->nextGameState() )
		{
			core->getState() = 1;
		}
		
		
		// Draw
		core->getWindow()->draw( menu_background->get() );
		git_button->draw( *core->getWindow() );
		google_button->draw( *core->getWindow() );
		twitter_button->draw( *core->getWindow() );
		facebook_button->draw( *core->getWindow() );
		menu_play_button->draw( core->getWindow() );
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
