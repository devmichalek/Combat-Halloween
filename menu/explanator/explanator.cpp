/**
    explanator.h
    Purpose: class Explanator - shows information

    @author Adrian Michalek
    @version 2017.03.02
	@email adrmic98@gmail.com
*/

#include "menu/explanator/explanator.h"

Explanator::Explanator()
{
	free();
}

Explanator::~Explanator()
{
	free();
}

void Explanator::free()
{
	text.free();
	bg.free();
	
	alpha = 0;
	vel = 0;
	state = 0;
	
	counter = 0;
	line = 0;
	alpha_line = 0;
}



void Explanator::load( string str )
{
	free();
	
	vel = 1;
	
	// Your text
	text.setName( "explanator-text" );
	text.setFont( "data/initialization/Jaapokki-Regular.otf", 14, 0, 0, 0 );
	text.setText( str );
	
	bg.setName( "explanator-bg" );
	bg.create( text.getWidth() +5, text.getHeight() +7 );
	bg.setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
	
	line = 140;
	alpha_line = 100;
}

void Explanator::draw( sf::RenderWindow &window )
{
	if( state > 1 )
	{
		alpha += vel;
		if( alpha >= alpha_line )
		{
			alpha = alpha_line;
		}
	}
	else
	{
		alpha -= vel;
		if( alpha <= 0 )
		{
			alpha = 0;
		}
	}
	
	if( counter > 0 )
	{
		counter ++;
	}
	
	if( alpha > 0 )
	{
		bg.setAlpha( alpha );
		window.draw( bg.get() );
		
		text.setAlpha( alpha );
		window.draw( text.get() );
	}
}

void Explanator::fadeout( int i, int min )
{
	state = 0;
	alpha = 0;
	bg.fadeout( i, min );
	text.fadeout( i, min );
}



void Explanator::run()
{
	if( counter == 0 )
	{
		counter = 1;
		state = 1;
		alpha = 0;
	}
}

void Explanator::stop()
{
	if( counter >= line )
	{
		if( alpha == 0 )
		{
			counter = 0;
		}
		
		state = 0;
	}
}

void Explanator::focus( float x, float y, bool side )
{
	if( state == 1 )
	{
		y -= bg.getHeight();
		
		if( side )
		{
			bg.setPosition( x, y );
			text.setPosition( x, y );
		}
		else
		{
			bg.setPosition( x -bg.getWidth(), y );
			text.setPosition( x -bg.getWidth(), y );
		}
		
		state = 2;
	}
}