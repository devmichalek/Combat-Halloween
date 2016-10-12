#include "engine.h"
#include <stdio.h>
#include <time.h>
#include <cstdlib>

// Create objects.
Engine::Engine()
{
    core = new Core( 1000, 750, -2 );
    core->load( "Ninja" );
	
	loading = new Loading;
	loading->load( core->getWidth(), core->getHeight() );
	
	intro = new Intro;
	
	menu = new Menu;
	
	level_menu = new Level_menu;
}


// Free objects.
void Engine::free()
{
	if( loading != NULL )	delete loading;
	if( intro != NULL )		delete intro;
	if( menu != NULL )		delete menu;
	if( level_menu != NULL )		delete level_menu;
	
	delete core;
}


// Load objects.
void Engine::load()
{
	loading->draw( core->getWindow() );
	
	switch( loading->getState() )
	{
		case 1:
		intro->load( core->getWidth(), core->getHeight() );
		break;
		
		case 2:
		menu->load( core->getWidth(), core->getHeight() );
		break;
		
		case 3:
		level_menu->load( core->getWidth(), core->getHeight() );
		break;
		
		case 99:
		srand( time( NULL ) );
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
		
		if( core->getState() == 1 ) // select level state
		{
			level_menu->handle( core->getEvent() );
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
			level_menu->set( menu->getState() );
			core->getState() = 1;
			menu->reloadMusic();
			Mix_HaltMusic();
			level_menu->reloadMusic();
		}
    }
	
	// select level state
	if( core->getState() == 1 )
    {
		level_menu->draw( core->getWindow() );
		if( level_menu->isQuit() )
		{
			core->isOpen() = false;
		}
		else if( level_menu->nextState() )
		{
			core->getState() = 2;
		}
		else if( level_menu->backToMenu() )
		{
			core->getState() = 0;
		}
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
