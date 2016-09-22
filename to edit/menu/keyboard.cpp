#include "keyboard.h"
#include <stdlib.h>
#include <string>


Keyboard::Keyboard()
{
    text_nr = 0;
	text = NULL;
	
	focus = 0;
	
	keys = NULL;
	keys_nr = 0;
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

	rect.free();
	focus = 0;
	
	delete [] keys;
	keys = NULL;
	keys_nr = 0;
}

void Keyboard::load( int screen_w, int bot )
{
	text_nr = 16;
	text = new MyText[ text_nr ];
	
	for( int i = 0; i < text_nr; i++ )
	{
		text[ i ].setID( "keyboard-text nr " + std::to_string( i ) );
		
		if( i <= 7 )
			text[ i ].setFont( "intro/Jaapokki-Regular.otf", 30, 0x98, 0x98, 0x98 );
		else
			text[ i ].setFont( "intro/Jaapokki-Regular.otf", 30, 0xFF, 0xFF, 0xFF );
	}
	
	
	text[ 0 ].setText( "Back" );
	text[ 0 ].setPosition( 20, bot + 40 );
	text[ 1 ].setText( "esc /locked" );
	text[ 1 ].setPosition( 300, bot + 40 );
	
	text[ 2 ].setText( "Quit" );
	text[ 2 ].setPosition( 20, text[ 0 ].getBot() + 6 );
	text[ 3 ].setText( "q /locked" );
	text[ 3 ].setPosition( 300, text[ 0 ].getBot() + 6 );
	
	text[ 4 ].setText( "Back in quit log" );
	text[ 4 ].setPosition( 20, text[ 2 ].getBot() + 6 );
	text[ 5 ].setText( "b /locked" );
	text[ 5 ].setPosition( 300, text[ 2 ].getBot() + 6 );
	
	text[ 6 ].setText( "Pause" );
	text[ 6 ].setPosition( 20, text[ 4 ].getBot() - 2 );
	text[ 7 ].setText( "p /locked" );
	text[ 7 ].setPosition( 300, text[ 4 ].getBot() - 2 );
	
	
	
	text[ 8 ].setText( "Jump" );
	text[ 8 ].setPosition( 20, text[ 6 ].getBot() + 90 );
	text[ 9 ].setText( "up" );
	text[ 9 ].setPosition( 300, text[ 6 ].getBot() + 90 );
	
	text[ 10 ].setText( "Attack" );
	text[ 10 ].setPosition( 20, text[ 8 ].getBot() - 2 );
	text[ 11 ].setText( "space" );
	text[ 11 ].setPosition( 300, text[ 8 ].getBot() - 2 );
	
	text[ 12 ].setText( "Move left" );
	text[ 12 ].setPosition( 20, text[ 10 ].getBot() + 6 );
	text[ 13 ].setText( "left" );
	text[ 13 ].setPosition( 300, text[ 10 ].getBot() + 6 );
	
	text[ 14 ].setText( "Move right" );
	text[ 14 ].setPosition( 20, text[ 12 ].getBot() + 6 );
	text[ 15 ].setText( "right" );
	text[ 15 ].setPosition( 300, text[ 12 ].getBot() + 6 );
	
	
	rect.create( 1, 1, sf::Color( 0x00, 0x00, 0x00 ) );
	rect.setAlpha( 35 );
	
	keys_nr = 6;
	keys = new int [ keys_nr ];
	keys[ 0 ] = 73;
	keys[ 1 ] = 57;
	keys[ 2 ] = 71;
	keys[ 3 ] = 72;
	keys[ 4 ] = 1;
	keys[ 5 ] = 15;
}

void Keyboard::draw( sf::RenderWindow &window )
{
	for( int i = 0; i < text_nr; i++ )
	{
		window.draw( text[ i ].get() );
	}
	
	//Rect
	if( focus != 0 )
	{
		window.draw( rect.get() );
	}
}

void Keyboard::handle( sf::Event &event )
{
	int x, y;
	
	if( event.type == sf::Event::MouseButtonPressed )
	{
		focus = 0;
		x = event.mouseButton.x;
		y = event.mouseButton.y;
		
		int add = 10;
		for( int i = 8; i <= 14; i += 2 )
		{
			if( text[ i ].checkCollision( x, y, 0, add  ) || text[ i + 1 ].checkCollision( x, y, 0, add ) )
			{
				focus = i;
				rect.setPosition( text[ i ].getX(), text[ i ].getY() );
				rect.setScale( text[ i + 1 ].getRight() - text[ i ].getX(), text[ 8 ].getHeight() + add );
			}
		}
	}
	
	if( focus != 0 )
	{
		static bool rel = false;
		if( event.type == sf::Event::KeyPressed && !rel )
		{
			rel = true;
			bool success = true;
			for( int i = 0; i < keys_nr; i++ )
			{
				if( event.key.code == keys[ i ] )
					success = false;
			}
			
			if( success )
			{
				for( int i = 0; i <= 25; i++ ) // from A ... Z
				{
					// b and p is used for back and pause
					if( event.key.code == i ) 
					{
						// printf( "%d -- %d\n", (focus -8) /2, i );
						keys[ (focus -8) /2 ] = i;
						
						std::string str = "";
						str += static_cast <char> ( i +97 );

						text[ focus +1 ].setText( str );
						text[ focus +1 ].reloadPosition();
						
						break;
					}
				}
				
				// Left
				if( event.key.code == 71 )
				{
					keys[ (focus -8) /2 ] = 71;
					text[ focus +1 ].setText( "left" );
					text[ focus +1 ].reloadPosition();
				}
				
				// Right
				else if( event.key.code == 72 )
				{
					keys[ (focus -8) /2 ] = 72;
					text[ focus +1 ].setText( "right" );
					text[ focus +1 ].reloadPosition();
				}
				
				// Up
				else if( event.key.code == 73 )
				{
					keys[ (focus -8) /2 ] = 73;
					text[ focus +1 ].setText( "up" );
					text[ focus +1 ].reloadPosition();
				}
				
				// Down
				else if( event.key.code == 74 )
				{
					keys[ (focus -8) /2 ] = 74;
					text[ focus +1 ].setText( "down" );
					text[ focus +1 ].reloadPosition();
				}
				
				// Space
				else if( event.key.code == 57 )
				{
					keys[ (focus -8) /2 ] = 57;
					text[ focus +1 ].setText( "space" );
					text[ focus +1 ].reloadPosition();
				}
				
				// Return
				else if( event.key.code == 58 )
				{
					keys[ (focus -8) /2 ] = 58;
					text[ focus +1 ].setText( "return" );
					text[ focus +1 ].reloadPosition();
				}
				
				// LAlt
				else if( event.key.code == 39 )
				{
					keys[ (focus -8) /2 ] = 39;
					text[ focus +1 ].setText( "L alt" );
					text[ focus +1 ].reloadPosition();
				}
				
				// RAlt
				else if( event.key.code == 43 )
				{
					keys[ (focus -8) /2 ] = 43;
					text[ focus +1 ].setText( "R alt" );
					text[ focus +1 ].reloadPosition();
				}
				
				
				// LControl
				else if( event.key.code == 37 )
				{
					keys[ (focus -8) /2 ] = 37;
					text[ focus +1 ].setText( "L control" );
					text[ focus +1 ].reloadPosition();
				}
				
				
				// RControl
				else if( event.key.code == 41 )
				{
					keys[ (focus -8) /2 ] = 41;
					text[ focus +1 ].setText( "R control" );
					text[ focus +1 ].reloadPosition();
				}
			}
		}
		else if( event.type == sf::Event::KeyReleased )
		{
			rel = false;
		}
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
	
	rect.fadeout( j, min );
}

int* Keyboard::getHeroKeys()
{
	int* array = new int [ 4 ];
	
	for( int i = 0; i < keys_nr; i ++ )
	{
		array[ i ] = keys[ i ];
	}
	
	return array;
}
