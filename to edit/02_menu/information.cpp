#include "menu/information.h"

Information::Information()
{
	nr = 0;
	text = NULL;
}

Information::~Information()
{
	free();
}

void Information::free()
{
	if( text != NULL )
	{
		for( int i = 0; i < nr; i++ )
		{
			text[ i ].free();
		}
		
		delete [] text;
		text = NULL;
		nr = 0;
	}
}

	
void Information::load( int screen_h )
{
	free();
	
	nr = 7;
	text = new MyText[ nr ];
	
	for( int i = 0; i < nr; i ++ )
	{
		text[ i ].setName( "information-text nr " + std::to_string( i ) );
		if( i != 1 || i != 3 || i != 5 )
			text[ i ].setFont( "data/fonts/Jaapokki-Regular.otf", 25, 0xFF, 0xFF, 0xFF );
	}
	//8Ca93e
	//8c001a
	text[ 5 ].setFont( "data/fonts/Jaapokki-Regular.otf", 25, 0x8C, 0x00, 0x1A );
	text[ 1 ].setFont( "data/fonts/Jaapokki-Regular.otf", 25, 0xFF, 0xDE, 0x00 );
	text[ 3 ].setFont( "data/fonts/Jaapokki-Regular.otf", 25, 0x8C, 0xA9, 0x3E );
	
	text[ 0 ].setText( "instructions: " );
	text[ 1 ].setText( "click on" );
	text[ 2 ].setText( " activity, press " );
	text[ 3 ].setText( "'+'" );
	text[ 4 ].setText( " to add, press " );
	text[ 5 ].setText( "'-'" );
	text[ 6 ].setText( " to remove" );
	
	text[ 0 ].setPosition( 10, screen_h - text[ 0 ].getHeight() - 20 );
	for( int i = 1; i < nr; i ++ )
	{
		text[ i ].setPosition( text[ i -1 ].getRight() + 10, text[ 0 ].getY() );
	}
}

void Information::draw( sf::RenderWindow &window )
{
	for( int i = 0; i < nr; i ++ )
	{
		window.draw( text[ i ].get() );
	}
}



void Information::fadein( int v, int max )
{
	for( int i = 0; i < nr; i ++ )
	{
		text[ i ].fadein( v, max );
	}
}

void Information::fadeout( int v, int min )
{
	for( int i = 0; i < nr; i ++ )
	{
		text[ i ].fadeout( v, min );
	}
}
