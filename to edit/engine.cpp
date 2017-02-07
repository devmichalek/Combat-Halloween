#include "engine.h"
#include <stdio.h>
#include <time.h>
#include <cstdlib>

// Create objects.
Engine::Engine()
{
	// Set seed.
	srand( static_cast <int> ( time( NULL ) ) );
	
	// Create and load core.
    core = new Core( 1000, 750, -2, 120 );	// new FPS
    core->load( "Ninja" );
	
	loading = new Loading;
	loading->load( core->getWidth(), core->getHeight() );
	
	intro = new Intro;
	
	menu = new Menu;
	
	level_menu = new Level_menu;
	
	loading_world = new Loading_world;
	
	play_wood = new Play_wood;
	play_halloween = new Play_halloween;
	play_desert = new Play_desert;
	play_winter = new Play_winter;
	
	panel_menu = new Panel_menu;
}


// Free objects.
void Engine::free()
{
	if( core != NULL )			delete core;
	if( loading != NULL )		delete loading;
	if( intro != NULL )			delete intro;
	if( menu != NULL )			delete menu;
	if( level_menu != NULL )	delete level_menu;
	if( loading_world != NULL ) delete loading_world;
	if( play_wood != NULL )		delete play_wood;
	if( play_halloween != NULL )delete play_halloween;
	if( play_desert != NULL )	delete play_desert;
	if( play_winter != NULL )	delete play_winter;
	if( panel_menu != NULL )	delete panel_menu;
}


// Load objects.
void Engine::load()
{
	loading->draw( core->getWindow() );
	
	switch( loading->getState() )
	{
		case 10:
		intro->load( core->getWidth(), core->getHeight() );
		break;
		
		case 20:
		menu->load( core->getWidth(), core->getHeight() );
		break;
		
		case 30:
		level_menu->load( core->getWidth(), core->getHeight() );
		break;
		
		case 35:
		loading_world->load( core->getWidth(), core->getHeight() );
		break;
		
		case 40:
		play_wood->load( core->getWidth(), core->getHeight() );
		break;
		
		case 50:
		play_halloween->load( core->getWidth(), core->getHeight() );
		break;
		
		case 60:
		play_desert->load( core->getWidth(), core->getHeight() );
		break;
		
		case 70:
		play_winter->load( core->getWidth(), core->getHeight() );
		break;
		
		case 80:
		panel_menu->load( core->getWidth(), core->getHeight() );
		break;
		
		case 90:
		srand( time( NULL ) );
		break;
		
		

		case 100:
		delete loading;
		loading = NULL;
		core->getState() = 1;	// intro state = -1
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

        if( core->getState() == 0 ) // if we currently have menu state
        {
			menu->handle( core->getEvent() );
        }
		
		if( core->getState() == 1 ) // select level state
		{
			level_menu->handle( core->getEvent() );
		}
		
		if( core->getState() == 3 ) // halloween state
		{
			play_halloween->handle( core->getEvent() );
		}
		
		if( core->getState() == 4 ) // wood state
		{
			play_wood->handle( core->getEvent() );
		}
		
		if( core->getState() == 5 ) // winter state
		{
			play_winter->handle( core->getEvent() );
		}
		
		if( core->getState() == 6 ) // desert state
		{
			play_desert->handle( core->getEvent() );
		}
		
		if( core->getState() == 7 ) // panel state
		{
			panel_menu->handle( core->getEvent() );
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
			
			menu->reloadMusic();
			level_menu->setSound();
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
			loading_world->setState( level_menu->getWorld() +3 );
			core->getState()++;
		}
		else if( level_menu->backToMenu() )
		{
			core->getState() = 0;
			level_menu->reset();
		}
	}
	
	
	// loading world state
	if( core->getState() == 2 )
	{
		loading_world->draw( core->getWindow() );
		
		if( loading_world->readyToLoad() )
		{
			if( loading_world->getState() == 3 )		load_world( play_halloween );
			else if( loading_world->getState() == 4 )	load_world( play_wood );
			else if( loading_world->getState() == 5 )	load_world( play_winter );
			else if( loading_world->getState() == 6 )	load_world( play_desert );
		}
		
		if( loading_world->nextState() )
		{
			core->getState() = loading_world->getState();
		}
	}
	
	
	// halloween state
	if( core->getState() == 3 )
	{
		play_halloween->draw( core->getWindow() );
		if( play_halloween->nextState() )
		{
			panel_menu->setState( core->getState() );
			core->getState() = 7;
			play_halloween->reset();
		}
	}
	
	
	// wood state
	if( core->getState() == 4 )
	{
		play_wood->draw( core->getWindow() );
		if( play_wood->nextState() )
		{
			panel_menu->setState( core->getState() );
			core->getState() = 7;
			play_wood->reset();
		}
	}
	
	
	// winter state
	if( core->getState() == 5 )
	{
		play_winter->draw( core->getWindow() );
		if( play_winter->nextState() )
		{
			panel_menu->setState( core->getState() );
			core->getState() = 7;
			play_winter->reset();
		}
	}
	
	
	// desert state
	if( core->getState() == 6 )
	{
		play_desert->draw( core->getWindow() );
		if( play_desert->nextState() )
		{
			panel_menu->setState( core->getState() );
			core->getState() = 7;
			play_desert->reset();
		}
	}
	
	
	// panel state
	if( core->getState() == 7 )
	{
		panel_menu->draw( core->getWindow() );
		
		if( panel_menu->backToMenu() )
		{
			core->getState() = 0;
			
			if( panel_menu->getState() == 3 )
			{
				play_halloween->load( core->getWidth(), core->getHeight() );
			}
			else if( panel_menu->getState() == 4 )
			{
				play_wood->load( core->getWidth(), core->getHeight() );
			}
			else if( panel_menu->getState() == 5 )
			{
				play_winter->load( core->getWidth(), core->getHeight() );
			}
			else if( panel_menu->getState() == 6 )
			{
				play_desert->load( core->getWidth(), core->getHeight() );
			}
		
			panel_menu->reset();
			level_menu->reset();
			loading_world->reset();
			Mix_HaltMusic();
		}
		else if( panel_menu->backToPlatform() )
		{
			core->getState() = panel_menu->getState();
			panel_menu->reset();
		}
	}
}







// We don't care about things below.
// They will be the same all the time.
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

template <typename world>
void Engine::load_world( world w )
{
	loading_world->setText( w->getInfo() );
	if( w->positioning( level_menu->getCharacter(),
						level_menu->getWorldsize(), 
						level_menu->getFlatness(),
						level_menu->getHoverness(),
						level_menu->getPugness() ) )
	{
		loading_world->setReady();
	}
}