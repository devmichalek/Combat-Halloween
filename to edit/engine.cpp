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
	
	character_menu = new Character_menu;
	
	play_wood = new Play_wood;
}


// Free objects.
void Engine::free()
{
	if( loading != NULL )	delete loading;
	if( intro != NULL )		delete intro;
	if( menu != NULL )		delete menu;
	if( level_menu != NULL )		delete level_menu;
	if( character_menu != NULL )	delete character_menu;
	if( play_wood != NULL )	delete play_wood;
	
	delete core;
}


// Load objects.
void Engine::load()
{
	loading->draw( core->getWindow() );
	
	switch( loading->getState() )
	{
		case 5:
		intro->load( core->getWidth(), core->getHeight() );
		break;
		
		case 15:
		menu->load( core->getWidth(), core->getHeight() );
		break;
		
		case 22:
		level_menu->load( core->getWidth(), core->getHeight() );
		break;
		
		case 35:
		character_menu->load( core->getWidth(), core->getHeight() );
		break;
		
		case 70:
		play_wood->load( core->getWidth(), core->getHeight() );
		break;
		
		case 99:
		srand( time( NULL ) );
		break;

		case 100:
		delete loading;
		loading = NULL;
		core->getState() = 2;	// intro state
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
		
		if( core->getState() == 2 ) // choose character state
		{
			character_menu->handle( core->getEvent() );
		}
		
		if( core->getState() == 4 ) // wood state
		{
			play_wood->handle( core->getEvent() );
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
			core->getState() = 1;
			level_menu->set( menu->getState() );
			
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
			character_menu->set( level_menu->getState() );
			
			level_menu->reloadMusic();
			Mix_HaltMusic();
			character_menu->reloadMusic();
		}
		else if( level_menu->backToMenu() )
		{
			core->getState() = 0;
		}
	}
	
	// character state
	if( core->getState() == 2 )
	{
		character_menu->draw( core->getWindow() );
		if( character_menu->nextState() )
		{
			core->getState() = level_menu->getMap() +3;
			character_menu->reloadMusic();
			Mix_HaltMusic();
		}
		else if( character_menu->backToMenu() )
		{
			core->getState() = 1;
			level_menu->resetChoice();
		}
	}
	
	
	
	
	// wood state
	if( core->getState() == 4 )
	{
		play_wood->draw( core->getWindow() );
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
