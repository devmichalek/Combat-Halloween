#include "engine.h"
#include <stdio.h>

// Create objects.
Engine::Engine()
{
    core = new Core( -2, 1024, 768 );
    core->load( "Ninja" );
	
	loading = new Loading;
	loading->load( core->getWidth(), core->getHeight() );
	
	intro = new Intro;
	
	menu = new Menu;
	
	// Create play objects
	game_timer = new Game_timer;
}


// Free objects.
void Engine::free()
{
	if( loading != NULL )	delete loading;
	if( intro != NULL )		delete intro;
	if( menu != NULL )		delete menu;
	
	delete game_timer;
	delete core;
}


// Load objects.
void Engine::load()
{
	loading->draw( core->getWindow(), 99 );
	
	switch( loading->getState() )
	{
		case 1:
		intro->load( core->getWidth(), core->getHeight() );
		break;
		
		case 2:
		menu->load( core->getWidth(), core->getHeight() );
		break;
		
		case 3:
		game_timer->load( core->getWidth() );
		break;

		case 100:
		delete loading;
		loading = NULL;
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

        if( core->getState() == 0 ) // if we actually have menu state
        {
			menu->handle( core->getEvent() );
        }
		
		if( core->getState() == 1 ) // if we actually have play state
		{
			game_timer->handle( core->getEvent() );
		}

    }
}

// Render objects.
void Engine::states()
{
	// loading state
	if( core->getState() == -2 )
	{
		load();
	}

	// intro state
	if( core->getState() == -1 )
	{
		intro->draw( core->getWindow() );
		if( intro->isQuit() )
		{
			delete intro;
			intro = NULL;
			core->getState() = 0;
		}
	}
	
	// menu state
    if( core->getState() == 0 )
    {
		menu->draw( core->getWindow() );
		if( menu->isQuit() )
		{
			core->isOpen() = false;
		}
		else if( menu->nextState() )
		{
			delete menu;
			menu = NULL;
			core->getState() = 1;
		}
    }
	
	// play state
	if( core->getState() == 1 )
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
