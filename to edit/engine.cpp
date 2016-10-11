#include "engine.h"
#include <stdio.h>

// Create objects.
Engine::Engine()
{
    core = new Core( 900, 700, -1 );
	leftSide = new MySprite();
}


// Free objects.
void Engine::free()
{
	delete core;
	delete leftSide;
}

void Engine::load()
{
	core->load( "Map" );
	core->setColor( 0xFF, 0xFF, 0xFF );
	
	leftSide->create( core->getWidth() /9 *2, core->getHeight() );
	leftSide->setColor( sf::Color( 0xF0, 0xEC, 0xEB ) );
	leftSide->setAlpha( 0xFF );
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
    }
}

// Render objects.
void Engine::states()
{
	core->getWindow()->draw( leftSide->get() );
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
