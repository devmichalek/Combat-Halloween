#include "engine.h"
#include <stdio.h>
#include <time.h>
#include <cstdlib>

// Create objects.
Engine::Engine()
{
    core = new Core( 1000, 750, -2, 120 );
    core->load( "Ninja" );
	
	loading = new Loading;
	loading->load( core->getWidth(), core->getHeight() );
	
	intro = new Intro;
	
	menu = new Menu;
	
	level_menu = new Level_menu;
	
	play_wood = new Play_wood;
	play_halloween = new Play_halloween;
	play_desert = new Play_desert;
	play_winter = new Play_winter;
}


// Free objects.
void Engine::free()
{
	if( loading != NULL )	delete loading;
	if( intro != NULL )		delete intro;
	if( menu != NULL )		delete menu;
	if( level_menu != NULL )		delete level_menu;
	if( play_wood != NULL )	delete play_wood;
	if( play_halloween != NULL )	delete play_halloween;
	if( play_desert != NULL )	delete play_desert;
	if( play_winter != NULL )	delete play_winter;
	
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
		
		case 4:
		play_wood->load( core->getWidth(), core->getHeight() );
		break;
		
		case 5:
		play_halloween->load( core->getWidth(), core->getHeight() );
		break;
		
		case 6:
		play_desert->load( core->getWidth(), core->getHeight() );
		break;
		
		case 7:
		play_winter->load( core->getWidth(), core->getHeight() );
		break;
		
		case 8:
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
		
		if( core->getState() == 2 ) // winter state
		{
			play_winter->handle( core->getEvent() );
		}
		
		if( core->getState() == 3 ) // wood state
		{
			play_wood->handle( core->getEvent() );
		}
		
		if( core->getState() == 4 ) // desert state
		{
			play_desert->handle( core->getEvent() );
		}
		
		if( core->getState() == 5 ) // halloween state
		{
			play_halloween->handle( core->getEvent() );
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
			core->getState() = level_menu->getMap() +2;
			
			if( core->getState() == 2 ) play_winter->setHero( core->getWidth(), core->getHeight(), level_menu->getCharacter() );
			else if( core->getState() == 3 ) play_wood->setHero( core->getWidth(), core->getHeight(), level_menu->getCharacter() );
			else if( core->getState() == 4 ) play_desert->setHero( core->getWidth(), core->getHeight(), level_menu->getCharacter() );
			else if( core->getState() == 5 ) play_halloween->setHero( core->getWidth(), core->getHeight(), level_menu->getCharacter() );
			
			level_menu->reloadMusic();
			Mix_HaltMusic();
		}
		else if( level_menu->backToMenu() )
		{
			core->getState() = 0;
		}
	}
	
	// winter state
	if( core->getState() == 2 )
	{
		play_winter->draw( core->getWindow() );
	}
	
	// wood state
	if( core->getState() == 3 )
	{
		play_wood->draw( core->getWindow() );
	}
	
	// desert state
	if( core->getState() == 4 )
	{
		play_desert->draw( core->getWindow() );
	}
	
	// halloween state
	if( core->getState() == 5 )
	{
		play_halloween->draw( core->getWindow() );
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
