#include "engine.h"
#include <stdio.h>
#include <cstdlib>

// Create objects.
Engine::Engine()
{
	// Set seed.
	srand( static_cast <int> ( time( NULL ) ) );
	
	// Create and load core.
    core = new Core( 1000, 750, -2/*, 180*/ );
    core->load( "Ninja" );
	
	timer = new Timer( 200 );
	
	loading = new Loading;
	loading->load( core->getWidth(), core->getHeight() );
	
	intro = new Intro;
	
	menu = new Menu;
	
	level = new Level;
	
	gears = new Loading_world;
	
	halloween = new Halloween;
	forest = new Forest;
	winter = new Winter;
	desert = new Desert;
	
	panel = new Panel_menu;
}


// Free objects.
void Engine::free()
{
	if( core != NULL )			delete core;
	if( timer != NULL )			delete timer;
	
	if( loading != NULL )		delete loading;
	if( intro != NULL )			delete intro;
	if( menu != NULL )			delete menu;
	if( level != NULL )			delete level;
	
	
	if( halloween != NULL )		delete halloween;
	if( forest != NULL )		delete forest;
	if( winter != NULL )		delete winter;
	if( desert != NULL )		delete desert;
	
	
	if( gears != NULL ) 	delete gears;
	if( panel != NULL )		delete panel;
}


// Load objects.
void Engine::load()
{
	loading->draw( core->getWindow() );
	
	switch( loading->getState() )
	{
		case 10:	intro->load( core->getWidth(), core->getHeight() );	break;
		
		case 20:	menu->load( core->getWidth(), core->getHeight() );	break;
		
		case 30:	level->load( core->getWidth(), core->getHeight() );	break;
		
		case 35:	gears->load( core->getWidth(), core->getHeight() );	break;

		case 40:	halloween->load( core->getWidth(), core->getHeight(), timer->getFPS() );	break;
		case 50:	forest->load( core->getWidth(), core->getHeight(), timer->getFPS() );	break;
		case 60:	winter->load( core->getWidth(), core->getHeight(), timer->getFPS() );	break;
		case 70:	desert->load( core->getWidth(), core->getHeight(), timer->getFPS() );	break;
		
		case 80:	panel->load( core->getWidth(), core->getHeight() );	break;
		
		case 90:	srand( time( NULL ) );	break;
		
		case 100:
		delete loading;
		loading = NULL;
		core->getState() = 0;	// intro state = -1
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
		
		switch( core->getState() )
		{
			case MENU: 	menu->handle( core->getEvent() ); 			break;
			case LEVEL:	level->handle( core->getEvent() );			break;
			case HALLOWEEN: halloween->handle( core->getEvent() );	break;
			case FOREST: forest->handle( core->getEvent() );		break;
			case WINTER: winter->handle( core->getEvent() );		break;
			case DESERT: desert->handle( core->getEvent() );		break;
			case PANEL: panel->handle( core->getEvent() );			break;
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
	if( core->getState() == INTRO )
	{
		intro->draw( core->getWindow() );
		if( intro->isQuit() )
		{
			delete intro;
			intro = NULL;
			core->getState() = MENU;
		}
	}
	
	
	// menu state
    if( core->getState() == MENU )
    {
		menu->draw( core->getWindow() );
		if( menu->isQuit() )
		{
			core->isOpen() = false;
		}
		else if( menu->nextState() )
		{
			core->getState() = LEVEL;
			
			menu->reloadMusic();
			level->setSound();
			level->reloadMusic();
		}
    }
	
	
	// select level state
	if( core->getState() == LEVEL )
    {
		level->draw( core->getWindow() );
		if( level->isQuit() )
		{
			core->isOpen() = false;
		}
		else if( level->nextState() )
		{
			gears->setState( level->getWorld() );
			core->getState() = GEARS;
		}
		else if( level->backToMenu() )
		{
			core->getState() = MENU;
			level->reset();
		}
	}
	
	
	// loading world state
	if( core->getState() == GEARS )
	{
		gears->draw( core->getWindow() );
		
		if( gears->readyToLoad() )
		{
			if( gears->getState() == HALLOWEEN )		load_world( halloween );
			else if( gears->getState() == FOREST )		load_world( forest );
			else if( gears->getState() == WINTER )		load_world( winter );
			else if( gears->getState() == DESERT )		load_world( desert );
		}
		
		if( gears->nextState() )
		{
			core->getState() = gears->getState();
		}
	}
	
	
	// halloween state
	if( core->getState() == HALLOWEEN )
	{
		halloween->draw( core->getWindow() );
		if( halloween->nextState() )
		{
			panel->setState( core->getState() );
			core->getState() = PANEL;
			halloween->reset();
		}
	}
	
	
	// forest state
	if( core->getState() == FOREST )
	{
		forest->draw( core->getWindow() );
		if( forest->nextState() )
		{
			panel->setState( core->getState() );
			core->getState() = PANEL;
			forest->reset();
		}
	}
	
	
	// winter state
	if( core->getState() == WINTER )
	{
		winter->draw( core->getWindow() );
		if( winter->nextState() )
		{
			panel->setState( core->getState() );
			core->getState() = PANEL;
			winter->reset();
		}
	}
	
	
	// desert state
	if( core->getState() == DESERT )
	{
		desert->draw( core->getWindow() );
		if( desert->nextState() )
		{
			panel->setState( core->getState() );
			core->getState() = PANEL;
			desert->reset();
		}
	}
	
	
	// panel state
	if( core->getState() == PANEL )
	{
		panel->draw( core->getWindow() );
		
		if( panel->backToMenu() )
		{
			core->getState() = MENU;
			
			if( panel->getState() == HALLOWEEN )
			{
				halloween->load( core->getWidth(), core->getHeight(), timer->getFPS() );
			}
			else if( panel->getState() == FOREST )
			{
				forest->load( core->getWidth(), core->getHeight(), timer->getFPS() );
			}
			else if( panel->getState() == WINTER )
			{
				winter->load( core->getWidth(), core->getHeight(), timer->getFPS() );
			}
			else if( panel->getState() == DESERT )
			{
				desert->load( core->getWidth(), core->getHeight(), timer->getFPS() );
			}
		
			panel->reset();
			level->reset();
			gears->reset();
			Mix_HaltMusic();
		}
		else if( panel->backToPlatform() )
		{
			core->getState() = panel->getState();
			panel->reset();
		}
	}
}







// We don't care about things below.
// They will be the same all time.
void Engine::loop()
{
    while( core->isOpen() )
    {
		timer->start();
        core->clear();

        events();
        states();

        core->display();
		timer->setFPS();
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
	gears->setText( w->getInfo() );
	if( w->positioning( level->getCharacter(),
						level->getWorldsize(), 
						level->getFlatness(),
						level->getDifficulty() ) )
	{
		gears->setReady();
	}
}