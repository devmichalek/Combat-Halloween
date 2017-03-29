#include "02_menu/explanator/explanator.h"

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
	screen_w = 0;
	
	counter = 0;
	line = 0;
	alpha_line = 0;
}



void Explanator::load( string str, int screen_w )
{
	free();
	
	vel = 1;
	this->screen_w = screen_w;
	
	// Your text
	text.setName( "explanator-text" );
	text.setFont( "data/00_loading/Jaapokki-Regular.otf", 20, 0xFF, 0xFF, 0xFF );
	text.setText( str );
	
	bg.setName( "explanator-bg" );
	bg.create( text.getWidth() +5, text.getHeight() +7 );
	bg.setColor( sf::Color( 0, 0, 0 ) );
	
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

void Explanator::focus( int x, int y )
{
	if( state == 1 && x > 0 && x < screen_w && y > 0 && y < screen_w )
	{
		y -= bg.getHeight();
		bg.setPosition( x, y );
		text.setPosition( x, y );
		if( x +bg.getWidth() > screen_w )
		{
			bg.setPosition( x -bg.getWidth(), y );
			text.setPosition( x -bg.getWidth(), y );
		}
		
		state = 2;
	}
}

void Explanator::fadeout( int i, int min )
{
	state = 0;
	alpha = 0;
	bg.fadeout( i, min );
	text.fadeout( i, min );
}
