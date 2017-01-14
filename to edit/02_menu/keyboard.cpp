#include "keyboard.h"
#include <stdlib.h>
#include <string>


Keyboard::Keyboard()
{
    text_nr = 0;
	text = NULL;
}

Keyboard::~Keyboard()
{
	if( text != NULL )
	{
		for( int i = 0; i < text_nr; i++ )
		{
			text[ i ].free();
		}
		
		delete [] text;
		text = NULL;
		text_nr = 0;
	}
}

void Keyboard::load( int right, int top )
{
	text_nr = 8;
	text = new MyText[ text_nr ];
	
	for( int i = 0; i < text_nr; i++ )
	{
		text[ i ].setName( "keyboard-text nr " + std::to_string( i ) );
		text[ i ].setFont( "data/fonts/Jaapokki-Regular.otf", 25, 0x98, 0x98, 0x98 );
	}
	
	
	text[ 0 ].setText( "Back" );
	text[ 1 ].setText( "esc" );
	
	text[ 2 ].setText( "Quit" );
	text[ 3 ].setText( "q" );
	
	text[ 4 ].setText( "Back in quit log" );
	text[ 5 ].setText( "b" );
	
	text[ 6 ].setText( "Pause" );
	text[ 7 ].setText( "p" );
	
	text[ 0 ].setPosition( right + 120, top );
	text[ 1 ].setPosition( right + 350, top );
	for( int i = 2; i < text_nr -1; i += 2 )
	{
		text[ i ].setPosition( right + 120, text[ i -2 ].getBot() + 10 );
		text[ i +1 ].setPosition( right + 350, text[ i -2 ].getBot() + 10 );
	}
	
	text[ 6 ].setPosition( text[ 6 ].getX() , text[ 6 ].getY() -7 );
	text[ 7 ].setPosition( text[ 7 ].getX() , text[ 7 ].getY() -8 );
}

void Keyboard::draw( sf::RenderWindow &window )
{
	for( int i = 0; i < text_nr; i++ )
	{
		window.draw( text[ i ].get() );
	}
}

void Keyboard::fadein( int j, int max )
{
	for( int i = 0; i < text_nr; i++ )
	{
		text[ i ].fadein( j, max );
	}
}

void Keyboard::fadeout( int j, int min )
{
	for( int i = 0; i < text_nr; i++ )
	{
		text[ i ].fadeout( j, min );
	}
}