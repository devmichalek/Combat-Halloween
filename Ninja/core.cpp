#include "core.h"
#include <stdio.h>

Core::Core( unsigned width, unsigned height, unsigned FPS )
{
    state = 0;
    open = true;

    this->FPS = FPS;
    this->width = width;
    this->height = height;

    window = NULL;
}

Core::~Core()
{
    free();
}



void Core::free()
{
    if( window != NULL )
    {
        window->close();
        delete window;
        window = NULL;

        state = 0;
        open = true;

        width = 0;
        height = 0;

        color.r = 0;
        color.g = 0;
        color.b = 0;
        color.a = 0;
    }
}

bool Core::load( string title )
{
    bool success = true;

    free();

    window = new RenderWindow( VideoMode( width, height ), title, Style::Titlebar | Style::Close );
    if( window == NULL )
    {
        printf( "Not created window!\n" );
        success = false;
    }
    else
    {
        window->setFramerateLimit( FPS );
        printf( "Created window!\n" );
    }


    return success;
}




Event& Core::getEvent()
{
    return event;
}

RenderWindow*& Core::getWindow()
{
    return window;
}



void Core::clear()
{
    window->clear( color );

    if( window->getSize() != Vector2u( width, height ) )
    {
        width = window->getSize().x;
        height = window->getSize().y;
    }
}

void Core::display()
{
    window->display();
}

void Core::setVisible( bool visible )
{
    window->setVisible( visible );
}

void Core::setColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a )
{
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
}



int& Core::getState()
{
    return state;
}

bool& Core::isOpen()
{
    return open;
}



unsigned Core::getWidth()
{
    return width;
}

unsigned Core::getHeight()
{
    return height;
}
