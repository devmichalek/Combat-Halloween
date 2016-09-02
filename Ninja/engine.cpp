#include "engine.h"
#include <stdio.h>

// Create objects.
Engine::Engine()
{
    core = new Core( 1000, 750 );
	
	git_button = new Link_button( "https://github.com/Adriqun" );
	google_button = new Link_button( "https://en.wikipedia.org/wiki/Ninja" );
	twitter_button = new Link_button( "empty", true );
	facebook_button = new Link_button( "empty", true );
}


// Free objects.
void Engine::free()
{
    delete core;
	
	delete git_button;
	delete google_button;
	delete twitter_button;
	delete facebook_button;
}


// Load objects.
bool Engine::load()
{
    if( !core->load( "Ninja" ) ) return false;
	
	if( !git_button->load( "menu/git.png", core->getWidth() ) ) 									return false;
	if( !google_button->load( "menu/google.png", core->getWidth(), git_button->getBot() ) ) 		return false;
	if( !twitter_button->load( "menu/twitter.png", core->getWidth(), google_button->getBot() ) ) 	return false;
	if( !facebook_button->load( "menu/facebook.png", core->getWidth(), twitter_button->getBot() ) ) return false;

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
			git_button->handle( core->getEvent() );
			google_button->handle( core->getEvent() );
			twitter_button->handle( core->getEvent() );
			facebook_button->handle( core->getEvent() );
        }

    }
}

// Render objects.
void Engine::states()
{
    if( core->getState() == 0 ) // menu state
    {
		git_button->draw( *core->getWindow() );
		google_button->draw( *core->getWindow() );
		twitter_button->draw( *core->getWindow() );
		facebook_button->draw( *core->getWindow() );
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
