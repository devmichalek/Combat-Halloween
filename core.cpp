<<<<<<< HEAD
/**
    core.h
    Purpose: class Core responsible for sending renderer, accessing start valuables etc.

    @author Adrian Michalek
    @version 2016.08.19
	@email adrmic98@gmail.com
*/

#include "core.h"
#include <stdio.h>
#include <SDL2/SDL_mixer.h>

Core::Core( unsigned w, unsigned h, int state )
{
	this->state = state;
	open = true;
	
    width = w;
	height = h;
	
	// printf( /*"\x1B[1mFPS\x1B[0m=%d  */"\x1B[33mscreen_width\x1B[0m=%d  \x1B[33mscreen_height\x1B[0m=%d\n"/*, FPS*/, width, height );
=======
#include "core.h"
// #include <SFML/OpenGL.hpp>
// #include <stdio.h>

Core::Core( int state )
{
	this->width = 0;
	this->height = 0;
	
	this->state = state;
	open = true;
>>>>>>> Combat-Halloween/master

    window = NULL;
	
	color.r = 21;
	color.g = 21;
	color.b = 29;
	color.a = 0xFF;
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
<<<<<<< HEAD
		
		Mix_Quit();
    }
}

bool Core::load( string title )
=======
    }
}

bool Core::set( std::string title, int style )
>>>>>>> Combat-Halloween/master
{
    bool success = true;

    free();
<<<<<<< HEAD

    window = new sf::RenderWindow( sf::VideoMode( width, height ), title, sf::Style::Fullscreen );
=======
	
	// Find correct window size.
	// height / width = 0.5625
	int screen_width = sf::VideoMode::getDesktopMode().width /1.15;
	this->width = screen_width;
	// Security.
	if( this->width > 2560 )
	{
		this->width = 2560;
	}
	else if( this->width < 900 )
	{
		return false;
	}
	this->height = this->width *0.5625;
	// printf( "%d %d\n", width, height );
	
	/*
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 8;
	settings.majorVersion = 3;
	settings.minorVersion = 0;
	*/
    window = new sf::RenderWindow( sf::VideoMode( width, height ), title.c_str(), style/*, settings*/ );
>>>>>>> Combat-Halloween/master
    if( window == NULL )
    {
        printf( "Not created window!\n" );
        success = false;
    }
    else
    {
<<<<<<< HEAD
        // window->setFramerateLimit( FPS );
        // printf( "\x1B[97;1mCreated window!\x1B[0m\n" );

		if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
		{
			printf( "Mix could not initialize! Error: %s\n", Mix_GetError() );
			success = false;
		}
		else
		{
			Mix_AllocateChannels( 0xFF );
		}
	}
	
	// printf( "%d %d\n", window->getSize().x, window->getSize().y );
	
	width = window->getSize().x;
	height = window->getSize().y;
	
=======
		// glEnable(GL_TEXTURE_2D);
		sf::Image icon;
		std::string path = "images/initialization/icon.png";
		icon.loadFromFile( path.c_str() );
		window->setIcon( icon.getSize().x, icon.getSize().y, icon.getPixelsPtr() );
		// window->setFramerateLimit( 10 );
	}
	
>>>>>>> Combat-Halloween/master
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
<<<<<<< HEAD
    window->clear( color );
=======
    // glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	//window->pushGLStates();
	window->clear( color );
>>>>>>> Combat-Halloween/master
}

void Core::display()
{
<<<<<<< HEAD
=======
	// window->popGLStates();
>>>>>>> Combat-Halloween/master
    window->display();
}



<<<<<<< HEAD
=======
void Core::setView( sf::View view )
{
	window->setView( view );
}

void Core::resetView()
{
	window->setView( window->getDefaultView() );
}



>>>>>>> Combat-Halloween/master
void Core::setVisible( const bool& visible )
{
    window->setVisible( visible );
}

void Core::setColor( const sf::Color& color )
{
    this->color.r = color.r;
    this->color.g = color.g;
    this->color.b = color.b;
    this->color.a = color.a;
}



int& Core::getState()
{
    return state;
}

bool& Core::isOpen()
{
    return open;
}



<<<<<<< HEAD
const unsigned Core::getWidth() const
=======
const int& Core::getWidth() const
>>>>>>> Combat-Halloween/master
{
    return width;
}

<<<<<<< HEAD
const unsigned Core::getHeight() const
{
    return height;
=======
const int& Core::getHeight() const
{
    return height;
}

const double Core::getElapsedTime()
{
	double elapsedTime = static_cast <double> (clock.getElapsedTime().asMicroseconds()) /1000000; // per sec
    clock.restart();
	
	return elapsedTime;
>>>>>>> Combat-Halloween/master
}