#include "core.h"
#include <stdio.h>
#include <SDL2/SDL_mixer.h>

#ifdef __linux__
Core::Core( int w, int h, int state, int FPS )
{
    this->state = state;
    open = true;

    this->FPS = FPS;
    width = w;
    height = h;
	
	printf( "\x1B[1mFPS\x1B[0m=%d  \x1B[33mscreen_width\x1B[0m=%d  \x1B[33mscreen_height\x1B[0m=%d\n", FPS, width, height );

    window = NULL;
}
#endif

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
		
		Mix_Quit();
    }
}

bool Core::load( string title )
{
    bool success = true;

    free();

    window = new sf::RenderWindow( sf::VideoMode( width, height ), title, sf::Style::Titlebar | sf::Style::Close );
    if( window == NULL )
    {
        printf( "Not created window!\n" );
        success = false;
    }
    else
    {
        window->setFramerateLimit( FPS );
        printf( "\x1B[97;1mCreated window!\x1B[0m\n" );

		if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
		{
			printf( "Mix could not initialize! Error: %s\n", Mix_GetError() );
			success = false;
		}
		
	}


    return success;
}




sf::Event& Core::getEvent()
{
    return event;
}

sf::RenderWindow*& Core::getWindow()
{
    return window;
}



void Core::clear()
{
    window->clear( color );

    if( window->getSize() != sf::Vector2u( width, height ) )
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

void Core::setColor( sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a )
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



int& Core::getWidth()
{
    return width;
}

int& Core::getHeight()
{
    return height;
}
