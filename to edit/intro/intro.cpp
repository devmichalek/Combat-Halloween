#include "intro.h"
#include "templates/file.h"

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
	File file;
	file.load( "data/intro_settings.txt" );
	
	shuriken.setName( "intro-shuriken" );
	shuriken.load( file.s( 0 ) );
	
	bg.setName( "intro-background" );
	bg.create( screen_w, screen_h );
	bg.setColor( sf::Color( file.i(1), file.i(2), file.i(3) ) );
	bg.setAlpha( file.i(4) );
		
	
	nr = 4;
	text = new MyText[ nr ];
	
	// WHEN NOTHING...
	text[ 0 ].setID( "intro-text[0]" );
	text[ 0 ].setFont( file.s(5), file.i(6), file.i(7), file.i(8), file.i(9) );
	text[ 0 ].setText( "When nothing makes sense..." );
	text[ 0 ].center( screen_w, screen_h );



	
	// NINJA
	text[ 1 ].setID( "intro-text[1]" );
	text[ 1 ].setFont( file.s(5), file.i(6), file.i(10), file.i(11), file.i(12) );
	text[ 1 ].setText( "Ninja" );
	text[ 1 ].setPosition( screen_w/2 - text[ 1 ].getWidth()/2 - shuriken.getWidth() -10, screen_h/2 - text[ 1 ].getHeight()/2 );
	shuriken.setPosition( text[ 1 ].getRight() + 10, screen_h/2 - shuriken.getHeight()/2 +10 );
	
	
	
	
	// ADRIAN MICHALEK
	text[ 2 ].setID( "intro-text[2]" );
	text[ 2 ].setFont( file.s(5), file.i(6), file.i(7), file.i(8), file.i(9) );
	text[ 2 ].setText( "Adrian Michalek" );
	text[ 2 ].center( screen_w, screen_h );

	
	
	// PRODUCED ...
	text[ 3 ].setID( "intro-text[3]" );
	text[ 3 ].setFont( file.s(5), file.i(6), file.i(10), file.i(11), file.i(12) );
	text[ 3 ].setText( "produced by" );
	text[ 3 ].center( screen_w, screen_h, 0, -text[ 2 ].getHeight()-10 );
	
	file.close();
}

void Intro::draw( sf::RenderWindow* &window )
{
	window->draw( bg.get() );
	if( text[ 0 ].getAlpha() < 255 )
	{
		text[ 0 ].fadein( 3 );
		
		window->draw( text[ 0 ].get() );
	}
	else if( text[ 1 ].getAlpha() < 255 )
	{
		text[ 1 ].fadein( 3 );
		shuriken.fadein( 3 );
		
		window->draw( text[ 1 ].get() );
		window->draw( shuriken.get() );
	}
	else if( text[ 2 ].getAlpha() < 255 )
	{
		text[ 2 ].fadein( 3 );
		text[ 3 ].fadein( 3 );
		
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
