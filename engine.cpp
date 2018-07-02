#include "engine.h"
#include <stdio.h>
#include <cstdlib>

<<<<<<< HEAD
// Create objects.
=======
>>>>>>> Combat-Halloween/master
Engine::Engine()
{
	// Set seed.
	srand( static_cast <int> ( time( NULL ) ) );
	
<<<<<<< HEAD
	// Create and load core.
    core = new Core( 1000, 650, -2 );
    core->load( "Ninja" );
	
	timer = new Timer( 220 );
	
	loading = new Loading;
	loading->load( core->getWidth(), core->getHeight() );
	
	initialization = new Initialization;
	
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
	
	if( initialization != NULL )	delete initialization;

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
=======
	// Set core.
	core = new Core( 0 );
	core->set( "Combat Halloween" );
	
	// Set loading.
	loading = new Loading;
	loading->load( core->getWidth(), core->getHeight() );
}

void Engine::free()
{
	delete core;
	delete login;
	delete menu;
	delete level;
	delete play;
	delete table;
	delete editor;
}

void Engine::load()
{
	loading->mechanics( core->getElapsedTime() );
>>>>>>> Combat-Halloween/master
	loading->draw( core->getWindow() );
	
	switch( loading->getState() )
	{
<<<<<<< HEAD
		case 1:		initialization->load( core->getWidth(), core->getHeight() );	break;
		
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
		core->getState() = INIT;
		break;
	}
}


// Control objects.
void Engine::events()
{
    while( core->getWindow()->pollEvent( core->getEvent() ) )
=======
		case 1:
		initialization = new Initialization;
		initialization->load( core->getWidth(), core->getHeight() );
		break;
		
		case 20:
		login = new Login;
		login->load( core->getWidth(), core->getHeight() );
		break;
		
		case 25:
		menu = new Menu;
		menu->load( core->getWidth(), core->getHeight() );
		break;
		
		case 70:
		level = new Level;
		level->load( core->getWidth(), core->getHeight() );
		break;
		
		case 71:
		play = new Play;
		play->load( core->getWidth(), core->getHeight() );
		break;
		
		case 95:
		table = new Table;
		table->load( core->getWidth(), core->getHeight() );
		break;
		
		case 96:
		editor = new Editor;
		editor->load( core->getWidth(), core->getHeight() );
		break;
		
		case 101:
		loading->beReady();
		break;
	}
	
	if( loading->isReady() )
	{
		delete loading;
		loading = NULL;
		core->getState() = EDITOR;	// SET FIRST STATE.
	}
}

void Engine::events()
{
	while( core->getWindow()->pollEvent( core->getEvent() ) )
>>>>>>> Combat-Halloween/master
    {
        if( core->getEvent().type == sf::Event::Closed )
        {
            core->isOpen() = false;
        }
		
		switch( core->getState() )
		{
<<<<<<< HEAD
			case INIT:	initialization->handle( core->getEvent() );	break;
			case MENU: 	menu->handle( core->getEvent() ); 			break;
			case LEVEL:	level->handle( core->getEvent() );			break;
			case HALLOWEEN: halloween->handle( core->getEvent() );	break;
			case FOREST: forest->handle( core->getEvent() );		break;
			case WINTER: winter->handle( core->getEvent() );		break;
			case DESERT: desert->handle( core->getEvent() );		break;
			case FUTURE: future->handle( core->getEvent() );		break;
			case PANEL: panel->handle( core->getEvent() );			break;
=======
			case LOGIN: 	login->handle( core->getEvent() ); 	break;
			case MENU: 		menu->handle( core->getEvent() ); 	break;
			case LEVEL: 	level->handle( core->getEvent() );	break;
			case PLAY: 		play->handle( core->getEvent() ); 	break;
			case TABLE: 	table->handle( core->getEvent() ); 	break;
			case EDITOR: 	editor->handle( core->getEvent() ); break;
>>>>>>> Combat-Halloween/master
		}
    }
}

<<<<<<< HEAD
// Render objects.
void Engine::states()
{
	// loading state
=======
void Engine::states()
{
>>>>>>> Combat-Halloween/master
	if( core->getState() == LOADING )
	{
		load();
	}
	
<<<<<<< HEAD
	// initialization state
	if( core->getState() == INIT )
	{
		initialization->draw( core->getWindow() );
		if( initialization->nextState() )
		{
			delete initialization;
			initialization = NULL;
			
			core->getState() = MENU;
			menu->setNick();
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
			menu->reloadMusic();
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
			setPanel( halloween );
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
			setPanel( forest );
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
			setPanel( winter );
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
			setPanel( desert );
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
			setPanel( future );
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
=======
	if( core->getState() == INIT )
	{
		initialization->mechanics( core->getElapsedTime() );
		initialization->draw( core->getWindow() );
		
		if( initialization->isReady() )
		{
			core->getState() = LOGIN;
			delete initialization;
			initialization = NULL;
		}
	}
	
	if( core->getState() == LOGIN )
	{
		login->mechanics( core->getElapsedTime() );
		login->draw( core->getWindow() );
		
		if( login->isReady() )
		{
			menu->setUsername( login->getUsername() );
			level->setUsername( login->getUsername() );
			play->setUsername( login->getUsername() );
			editor->setUsername( login->getUsername() );
			table->setUsername( login->getUsername() );
			core->getState() = MENU;
		}
	}
	
	if( core->getState() == MENU )
	{
		menu->loadSound();
		menu->head( core->getWindow(), core->getElapsedTime() );
		
		if( menu->isReady() )
		{
			menu->saveSound();
			core->getState() = LEVEL;
		}
		else if( menu->isClose() )
		{
			menu->saveSound();
			core->isOpen() = false;
		}
		else if( menu->isEditor() )
		{
			menu->saveSound();
			core->getState() = EDITOR;
		}
	}
	
	if( core->getState() == LEVEL )
	{
		level->loadSound();
		level->head( core->getWindow(), core->getElapsedTime() );
		
		if( level->isNext() )
		{
			level->saveSound();
			core->getState() = PLAY;
		}
		else if( level->isBack() )
		{
			level->saveSound();
			core->getState() = MENU;
		}
	}
	
	if( core->getState() == PLAY )
	{
		play->loadSound();
		play->head( core->getWindow(), core->getElapsedTime() );
		
		if( play->isMenu() )
		{
			play->saveSound();
			core->getState() = MENU;
		}
		else if( play->isLevel() )
		{
			play->saveSound();
			core->getState() = LEVEL;
		}
		else if( play->isTable() )
		{
			play->saveSound();
			core->getState() = TABLE;
		}
		else if( play->isEditor() )
		{
			play->saveSound();
			core->getState() = EDITOR;
		}
	}
	
	if( core->getState() == TABLE )
	{
		table->loadSound();
		table->head( core->getWindow(), core->getElapsedTime() );
		
		if( table->isMenu() )
		{
			table->saveSound();
			core->getState() = MENU;
		}
		else if( table->isLevel() )
		{
			table->saveSound();
			core->getState() = LEVEL;
		}
	}
	
	if( core->getState() == EDITOR )
	{
		editor->head( core->getWindow(), core->getElapsedTime() );
		
		if( editor->isBack() )
		{
			core->getState() = MENU;
		}
		else if( editor->isPlay() )
		{
			core->getState() = PLAY;
			play->setMessage( editor->getMessage() );
>>>>>>> Combat-Halloween/master
		}
	}
}

<<<<<<< HEAD






// We don't care about things below.
// They will be the same all time.
void Engine::loop()
{
    while( core->isOpen() )
    {
		timer->start();
=======
Engine::~Engine()
{
	free();
}

void Engine::loop()
{
	while( core->isOpen() )
    {
>>>>>>> Combat-Halloween/master
        core->clear();

        events();
        states();

        core->display();
<<<<<<< HEAD
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

template <typename world>
void Engine::setPanel( world w )
{
	panel->set( w->getScores(), w->getType(), 
				w->winState(), w->getCoruption(),
				w->getTimePlayed(), w->getDeactivatedMines(),
				w->getEarnedMoney() );
}
=======
    }
}
>>>>>>> Combat-Halloween/master
