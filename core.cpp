#include "core.h"
#include <stdio.h>

Core::Core( int state )
{
	this->width = 0;
	this->height = 0;
	
	this->state = state;
	open = true;

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
    }
}

bool Core::set( std::string title, int style )
{
    bool success = true;

    free();
	
	// Find correct window size.
	// height / width = 0.5625
	int screen_width = sf::VideoMode::getDesktopMode().width /1.25;
	this->width = screen_width;
	// Security.
	if( this->width > 2560 )
	{
		this->width = 2560;
	}
	this->height = this->width *0.5625;

    window = new sf::RenderWindow( sf::VideoMode( width, height ), title.c_str(), style );
    if( window == NULL )
    {
        printf( "Not created window!\n" );
        success = false;
    }
    else
    {
		sf::Image icon;
		std::string path = "images/icon/icon.png";
		icon.loadFromFile( path.c_str() );
		window->setIcon( icon.getSize().x, icon.getSize().y, icon.getPixelsPtr() );
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
}

void Core::display()
{
    window->display();
}



void Core::setView( sf::View view )
{
	window->setView( view );
}

void Core::resetView()
{
	window->setView( window->getDefaultView() );
}



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



const int& Core::getWidth() const
{
    return width;
}

const int& Core::getHeight() const
{
    return height;
}

const double Core::getElapsedTime()
{
	double elapsedTime = static_cast <double> (clock.getElapsedTime().asMicroseconds()) /1000000; // per sec
    clock.restart();
	
	return elapsedTime;
}