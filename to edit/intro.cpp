#include "intro.h"

Intro::Intro()
{
	//c = 0;
	nr = 0;
	quit = false;
	text = NULL;
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

	
bool Intro::load( int screen_w, int screen_h )
{
	shuriken.load( "intro/shuriken.png" );
	
	bg.setAlpha( 255 );
	bg.create( screen_w, screen_h, 0x15, 0x15, 0x1D );
		
	
	nr = 4;
	text = new MyText[ nr ];
	
	// WHEN NOTHING...
	text[ 0 ].setFont( "intro/Jaapokki-Regular.otf", 37, 0xFF, 0xFF, 0xFF );

	text[ 0 ].setText( "When nothing makes sense..." );

	text[ 0 ].setPosition( screen_w/2 - text[ 0 ].getWidth()/2, screen_h/2 - text[ 0 ].getHeight()/2 );

	
	
	// NINJA
	text[ 1 ].setFont( "intro/Jaapokki-Regular.otf", 37, 0x70, 0xB7, 0x59 );

	text[ 1 ].setText( "Ninja" );

	text[ 1 ].setPosition( screen_w/2 - text[ 1 ].getWidth()/2 - shuriken.getWidth() -10, screen_h/2 - text[ 1 ].getHeight()/2 );

	
	shuriken.setPosition( text[ 1 ].getRight() + 10, screen_h/2 - shuriken.getHeight()/2 +10 );
	
	
	
	
	// ADRIAN MICHALEK
	text[ 2 ].setFont( "intro/Jaapokki-Regular.otf", 37, 0xFF, 0xFF, 0xFF );

	text[ 2 ].setText( "Adrian Michalek" );

	text[ 2 ].setPosition( screen_w/2 - text[ 2 ].getWidth()/2, screen_h/2 - text[ 2 ].getHeight()/2 );

	
	
	// PRODUCED ...
	text[ 3 ].setFont( "intro/Jaapokki-Regular.otf", 37, 0x70, 0xB7, 0x59 );

	text[ 3 ].setText( "produced by" );
	
		text[ 3 ].setPosition( screen_w/2 - text[ 3 ].getWidth()/2, screen_h/2 - text[ 3 ].getHeight()/2 - text[ 2 ].getHeight() -10 );
	
	
	return true;
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
