#include "engine.h"
#include <stdio.h>
#include <cstdlib>

Engine::Engine()
{
	// Set seed.
	srand( static_cast <int> ( time( NULL ) ) );
	
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
	loading->draw( core->getWindow() );
	
	switch( loading->getState() )
	{
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
    {
        if( core->getEvent().type == sf::Event::Closed )
        {
            core->isOpen() = false;
        }
		
		switch( core->getState() )
		{
			case LOGIN: 	login->handle( core->getEvent() ); 	break;
			case MENU: 		menu->handle( core->getEvent() ); 	break;
			case LEVEL: 	level->handle( core->getEvent() );	break;
			case PLAY: 		play->handle( core->getEvent() ); 	break;
			case TABLE: 	table->handle( core->getEvent() ); 	break;
			case EDITOR: 	editor->handle( core->getEvent() ); break;
		}
    }
}

void Engine::states()
{
	if( core->getState() == LOADING )
	{
		load();
	}
	
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
		}
	}
}

Engine::~Engine()
{
	free();
}

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
