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
	
	timer = new Timer( 220 );
	
	loading = new Loading;
	loading->load( core->getWidth(), core->getHeight() );
	
	menu = new Menu;
	
	level = new Level;
	
	gears = new Loading_world;
	
	halloween = new Halloween;
	forest = new Forest;
	winter = new Winter;
	desert = new Desert;
	future = new Future;
	
	panel = new Panel_menu;
}


// Free objects.
void Engine::free()
{
	if( core != NULL )			delete core;
	if( timer != NULL )			delete timer;
	
	if( loading != NULL )		delete loading;

	if( menu != NULL )			delete menu;
	if( level != NULL )			delete level;
	
	
	if( halloween != NULL )		delete halloween;
	if( forest != NULL )		delete forest;
	if( winter != NULL )		delete winter;
	if( desert != NULL )		delete desert;
	if( future != NULL )		delete future;
	
	if( gears != NULL ) 	delete gears;
	if( panel != NULL )		delete panel;
}


// Load objects.
void Engine::load()
{
	loading->draw( core->getWindow() );
	
	switch( loading->getState() )
	{
		case 10:	menu->load( core->getWidth(), core->getHeight() );	break;
		
		case 12:	level->load( core->getWidth(), core->getHeight() );	break;
		
		case 14:	gears->load( core->getWidth(), core->getHeight() );	break;

		case 70:	halloween->load( core->getWidth(), core->getHeight(), timer->getFPS() );	break;
		case 71:	forest->load( core->getWidth(), core->getHeight(), timer->getFPS() );	break;
		case 72:	winter->load( core->getWidth(), core->getHeight(), timer->getFPS() );	break;
		case 73:	desert->load( core->getWidth(), core->getHeight(), timer->getFPS() );	break;
		case 74:	future->load( core->getWidth(), core->getHeight(), timer->getFPS() );	break;
		
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
			case FUTURE: future->handle( core->getEvent() );		break;
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
			
			level->loadCharacter();
			level->loadWorlds();
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
			else if( gears->getState() == FUTURE )		load_world( future );
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
		if( halloween->defeatState() ||halloween->winState() )
		{
			panel->setState( core->getState() );
			panel->set( halloween->getScores(), halloween->getType(), halloween->winState() );
			halloween->reset();
			panel->setSound();
			panel->reloadMusic();
			core->getState() = PANEL;
		}
	}
	
	
	// forest state
	if( core->getState() == FOREST )
	{
		forest->draw( core->getWindow() );
		if( forest->defeatState() ||forest->winState() )
		{
			panel->setState( core->getState() );
			panel->set( forest->getScores(), forest->getType(), forest->winState() );
			forest->reset();
			panel->setSound();
			panel->reloadMusic();
			core->getState() = PANEL;
		}
	}
	
	
	// winter state
	if( core->getState() == WINTER )
	{
		winter->draw( core->getWindow() );
		if( winter->defeatState() ||winter->winState() )
		{
			panel->setState( core->getState() );
			panel->set( winter->getScores(), winter->getType(), winter->winState() );
			winter->reset();
			panel->setSound();
			panel->reloadMusic();
			core->getState() = PANEL;
		}
	}
	
	
	// desert state
	if( core->getState() == DESERT )
	{
		desert->draw( core->getWindow() );
		if( desert->defeatState() ||desert->winState() )
		{
			panel->setState( core->getState() );
			panel->set( desert->getScores(), desert->getType(), desert->winState() );
			desert->reset();
			panel->setSound();
			panel->reloadMusic();
			core->getState() = PANEL;
		}
	}
	
	
	// future state
	if( core->getState() == FUTURE )
	{
		future->draw( core->getWindow() );
		if( future->defeatState() ||future->winState() )
		{
			panel->setState( core->getState() );
			panel->set( future->getScores(), future->getType(), future->winState() );
			future->reset();
			panel->setSound();
			panel->reloadMusic();
			core->getState() = PANEL;
		}
	}
	
	
	// panel state
	if( core->getState() == PANEL )
	{
		panel->draw( core->getWindow() );
		
		if( panel->backToMenu() )
		{
			core->getState() = MENU;
			menu->checkMoney();
			menu->reloadMusic();
			
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
			else if( panel->getState() == FUTURE )
			{
				future->load( core->getWidth(), core->getHeight(), timer->getFPS() );
			}
		
			panel->reset();
			level->reset();
			level->loadWorlds();
			gears->reset();
			Mix_HaltMusic();
		}
		else if( panel->backToPlatform() )
		{
			core->getState() = panel->getState();
			panel->reset();
			level->loadWorlds();
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