/**
    link_button.h
    Purpose: class Link_button - for buttons, after click open website with special url.

    @author Adrian Michalek
    @version 2016.10.16
	@email adrmic98@gmail.com
*/

#include "link_button.h"
#include <stdlib.h>


Link_button::Link_button( string url, bool locked )
{
	free();
	
	this->url = url;
	this->locked = locked;
}

Link_button::~Link_button()
{
	free();
}

void Link_button::free()
{
	url = "";
    locked = true;
	
	button.free();
	
	click.free();
	focus = false;
	play = true;
	
	explanator.free();
}



void Link_button::load( string path, float x, float y )
{
	button.setName( "link_button-" + path );
    button.load( path, 4 );
	button.setScale( 0.5, 0.5 );
	button.setPosition( x -button.getWidth() -10, y );
	
	if( locked )
	{
		button.setOffset( 3 );
	}
	else
	{
		click.setID( "link_button-" + path );
		click.load( "data/menu/click.wav", 50 );
	}
}

void Link_button::handle( sf::Event &event, bool side )
{
	if( event.type == sf::Event::MouseMoved )
	{
		int x, y;
		x = event.mouseMove.x;
		y = event.mouseMove.y;
			
		if( button.checkCollision( x, y ) )
		{
			explanator.run();
			explanator.focus( x, y, side );
		}
		else
		{
			explanator.stop();
		}
	}
	
	if( !locked && button.getAlpha() == 0xFF )
	{
		int x, y;
		button.setOffset( 0 );

		if( event.type == sf::Event::MouseMoved )
		{
			x = event.mouseMove.x;
			y = event.mouseMove.y;
				
			if( button.checkCollision( x, y ) )
			{
				button.setOffset( 1 );
			}
			else
			{
				focus = false;
			}
		}

		if( event.type == sf::Event::MouseButtonPressed )
		{
			x = event.mouseButton.x;
			y = event.mouseButton.y;
				
			if( button.checkCollision( x, y ) )
			{
				button.setOffset( 2 );
					
				if( play )
				{
					click.play();
				}
						
				focus = true;

				string command = "sensible-browser ";
				command += url.c_str();
				system( command.c_str() );
			}
		}
			
		if( event.type == sf::Event::MouseButtonReleased )
		{
			focus = false;
		}
			
		if( focus )
		{
			button.setOffset( 2 );
		}
	}
}

void Link_button::draw( sf::RenderWindow &window )
{
    window.draw( button.get() );
	explanator.draw( window );
}



void Link_button::fadein( int i, int max )
{
	button.fadein( i, max );
}

void Link_button::fadeout( int i, int min )
{
	button.fadeout( i, min );
	explanator.fadeout( i, min );
}



float Link_button::getBot()
{
	return button.getBot();
}

float Link_button::getWidth()
{
	return button.getWidth();
}

float Link_button::getHeight()
{
	return button.getHeight();
}



void Link_button::setExplanator( string line )
{
	explanator.load( line );
}