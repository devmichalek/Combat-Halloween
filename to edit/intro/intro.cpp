#include "intro.h"

Intro::Intro()
{
	text = NULL;
	
	nr = 0;
	quit = false;
}

Intro::~Intro()
{
	bg.free();
	shuriken.free();

	if( text != NULL )
	{
		for( int i = 0; i < nr; i++ )
			text[ i ].free();
		
		delete [] text;
		text = NULL;
		nr = 0;
	}
	
	quit = false;
}

	
void Intro::load( const int &screen_w, const int &screen_h )
{
	shuriken.setName( "intro-shuriken" );
	shuriken.load( "intro/shuriken.png" );
	
	bg.setName( "intro-background" );
	bg.create( screen_w, screen_h );
	bg.setColor( sf::Color( 0x15, 0x15, 0x1D ) );
	bg.setAlpha( 0xFF );
		
	
	nr = 4;
	text = new MyText[ nr ];
	
	// WHEN NOTHING...
	text[ 0 ].setID( "intro-text[0]" );
	text[ 0 ].setFont( "intro/Jaapokki-Regular.otf", 37, 0xFF, 0xFF, 0xFF );
	text[ 0 ].setText( "When nothing makes sense..." );
	text[ 0 ].center( screen_w, screen_h );

	
	
	// NINJA
	text[ 1 ].setID( "intro-text[1]" );
	text[ 1 ].setFont( "intro/Jaapokki-Regular.otf", 37, 0x70, 0xB7, 0x59 );
	text[ 1 ].setText( "Ninja" );
	text[ 1 ].setPosition( screen_w/2 - text[ 1 ].getWidth()/2 - shuriken.getWidth() -10, screen_h/2 - text[ 1 ].getHeight()/2 );
	shuriken.setPosition( text[ 1 ].getRight() + 10, screen_h/2 - shuriken.getHeight()/2 +10 );
	
	
	
	
	// ADRIAN MICHALEK
	text[ 2 ].setID( "intro-text[2]" );
	text[ 2 ].setFont( "intro/Jaapokki-Regular.otf", 37, 0xFF, 0xFF, 0xFF );
	text[ 2 ].setText( "Adrian Michalek" );
	text[ 2 ].center( screen_w, screen_h );

	
	
	// PRODUCED ...
	text[ 3 ].setID( "intro-text[3]" );
	text[ 3 ].setFont( "intro/Jaapokki-Regular.otf", 37, 0x70, 0xB7, 0x59 );
	text[ 3 ].setText( "produced by" );
	text[ 3 ].center( screen_w, screen_h, 0, -text[ 2 ].getHeight()-10 );
}

void Intro::draw( sf::RenderWindow* &window )
{
	window->draw( bg.get() );
	if( text[ 0 ].getAlpha() < 255 )
	{
		text[ 0 ].fadein( 3, 255 );
		
		window->draw( text[ 0 ].get() );
	}
	else if( text[ 1 ].getAlpha() < 255 )
	{
		text[ 1 ].fadein( 3, 255 );
		shuriken.fadein( 3, 255 );
		
		window->draw( text[ 1 ].get() );
		window->draw( shuriken.get() );
	}
	else if( text[ 2 ].getAlpha() < 255 )
	{
		text[ 2 ].fadein( 3, 255 );
		text[ 3 ].fadein( 3, 255 );
		
		window->draw( text[ 2 ].get() );
		window->draw( text[ 3 ].get() );
	}
	else
	{
		quit = true;
	}
}

bool Intro::isQuit()
{
	return quit;
}
