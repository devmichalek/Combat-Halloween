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
	delete loading;
	delete initialization;
	delete login;
	delete menu;
}

void Engine::load()
{
	loading->draw( core->getWindow(), core->getElapsedTime() );
	
	switch( loading->getState() )
	{
		case 1:
		initialization = new Initialization;
		initialization->load( core->getWidth(), core->getHeight() );
		break;
		
		case 2:
		login = new Login;
		login->load( core->getWidth(), core->getHeight() );
		break;
		
		case 3:
		menu = new Menu;
		menu->load( core->getWidth(), core->getHeight() );
		break;
		
		case 101:
		loading->beReady();
		break;
	}
	
	if( loading->isReady() )
	{
		delete loading;
		loading = NULL;
		core->getState() = INIT;
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
			case LOGIN: login->handle( core->getEvent() ); break;
			case MENU: menu->handle( core->getEvent() ); break;
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
		initialization->draw( core->getWindow(), core->getElapsedTime() );
		if( initialization->isReady() )
		{
			core->getState() = LOGIN;
		}
	}
	
	if( core->getState() == LOGIN )
	{
		login->draw( core->getWindow(), core->getElapsedTime() );
		if( login->isReady() )
		{
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
		
		if( menu->isClose() )
		{
			menu->saveSound();
			core->isOpen() = false;
		}
	}
	
	if( core->getState() == LEVEL )
	{
		
	}
	
	if( core->getState() == PLAY )
	{
		
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
