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
	
	x_state = 0;
	y_state = 0;
	y_buf = 0;
	
	screen_w = 0;
	screen_h = 0;
}



void Link_button::load( string path, unsigned w, unsigned h, float l, float y )
{
	scale = 0.45;
	screen_w = w;
	screen_h = h;
	
	button.setName( "link_button-" + path );
    button.load( path, 4 );
	
	x_state = w -(l -button.getWidth() -10);
	y_state = h -y;
	y_buf = y;
	
	button.setPosition( w -x_state, h -y_state );
	
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

void Link_button::handle( sf::Event &event, int r_x, int r_y, bool r )
{
	if( event.type == sf::Event::MouseMoved )
	{
		int x, y;
		x = event.mouseMove.x;
		y = event.mouseMove.y;
			
		if( button.checkCollision( x +r_x, y +r_y ) )
		{
			explanator.run();
			explanator.focus( x +r_x, y +r_y, r );
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
				
			if( button.checkCollision( x +r_x, y +r_y ) )
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
	return y_buf +button.getHeight() *scale;
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



void Link_button::setScale( float s_x, float s_y )
{
	button.setBasicScale( s_x, s_y );
	button.setScale( scale, scale );
	
	explanator.setScale( s_x, s_y );
}

void Link_button::setViewH( int w, int r_x, int r_y )
{
	// printf( "r_x %d\n", r_x );
	button.setPosition( w -(x_state *button.getXScale()) +r_x, ((screen_h -y_state) *button.getYScale() /scale) +r_y );
}

void Link_button::setViewW( int h, int r_x, int r_y )
{
	button.setPosition( ((screen_w -x_state) *button.getXScale() /scale ) +r_x, h -(y_state *button.getYScale()) +r_y );
}

/*
void Link_button::setViewH( int w, int h, int r_x, int r_y )
{
	button.setPosition( (w -(w -(x_state *(button.getXScale() /scale)))) +r_x, (h -(h -(y_state *button.getYScale() /scale))) +r_y );
}

void Link_button::setViewW( int w, int h, int r_x, int r_y )
{
	printf( "%d %d\n", h, r_y );
	printf( "----%d %d\n", h +r_y, 1 );
	
	button.setPosition( (w -(w -(x_state *(button.getXScale() /scale)))) +r_x, (h -(h -(y_state *button.getYScale() /scale))) +r_y );
}
*/