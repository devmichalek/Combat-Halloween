/**
    intro.h
    Purpose: class Intro - to show slides.

    @author Adrian Michalek
    @version 2016.10.12
	@email adrmic98@gmail.com
*/

#include "intro.h"

Intro::Intro()
{
	text = NULL;
	
	nr = 0;
	quit = false;
}

Intro::~Intro()
{
	free();
}

void Intro::free()
{
	bg.free();
	shuriken.free();

	if( text != NULL )
	{
		for( sf::Uint8 i = 0; i < nr; i++ )
		{
			text[ i ].free();
		}
		
		delete [] text;
		text = NULL;
	}
	
	nr = 0;
	quit = false;
}

	
void Intro::load( const int &screen_w, const int &screen_h )
{
	free();
	
	shuriken.setName( "intro-kunai" );
	shuriken.load( "data/sprites/hero/kunai.png" );
	shuriken.setScale( 0.7, 0.7 );
	
	bg.setName( "intro-background" );
	bg.create( screen_w, screen_h );
	bg.setColor( sf::Color( 21, 21, 29 ) );
	bg.setAlpha( 0xFF );
		
	
	nr = 4;
	text = new MyText[ nr ];
	
	for( int i = 0; i < nr; i ++ )
	{
		text[ i ].setName( "intro-text[" + to_string(i) + "]" );
	}
	
	// WHEN NOTHING...
	text[ 0 ].setFont( "data/fonts/Jaapokki-Regular.otf", 37, 255, 255, 255 );
	text[ 0 ].setText( "When nothing makes sense..." );
	text[ 0 ].center( screen_w, screen_h );

	
	// NINJA
	text[ 1 ].setFont( "data/fonts/Jaapokki-Regular.otf", 37, 112, 183, 89 );
	text[ 1 ].setText( "Ninja" );
	text[ 1 ].setPosition( screen_w/2 - text[ 1 ].getWidth()/2 -40, screen_h/2 - text[ 1 ].getHeight()/2 );
	shuriken.setPosition( text[ 1 ].getRight() + 10, screen_h/2 - shuriken.getHeight()/2 +10 );
	
	
	// ADRIAN MICHALEK
	text[ 2 ].setFont( "data/fonts/Jaapokki-Regular.otf", 37, 255, 255, 255 );
	text[ 2 ].setText( "Adrian Michalek" );
	text[ 2 ].center( screen_w, screen_h );


	// PRODUCED ...
	text[ 3 ].setFont( "data/fonts/Jaapokki-Regular.otf", 37, 112, 183, 89 );
	text[ 3 ].setText( "produced by" );
	text[ 3 ].center( screen_w, screen_h, 0, -text[ 2 ].getHeight()-10 );
}

void Intro::draw( sf::RenderWindow* &window )
{
	window->draw( bg.get() );
	if( text[ 0 ].getAlpha() < 0xFF )
	{
		text[ 0 ].fadein( 1 );
		
		window->draw( text[ 0 ].get() );
	}
	else if( text[ 1 ].getAlpha() < 0xFF )
	{
		text[ 1 ].fadein( 1 );
		shuriken.fadein( 1 );
		
		window->draw( text[ 1 ].get() );
		window->draw( shuriken.get() );
	}
	else if( text[ 2 ].getAlpha() < 0xFF )
	{
		text[ 2 ].fadein( 1 );
		text[ 3 ].fadein( 1 );
		
		window->draw( text[ 2 ].get() );
		window->draw( text[ 3 ].get() );
	}
	else
	{
		quit = true;
	}
}

const bool& Intro::isQuit() const
{
	return quit;
}
