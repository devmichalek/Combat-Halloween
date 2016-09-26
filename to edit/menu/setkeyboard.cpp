#include "setkeyboard.h"
#include <stdio.h>
#include <string>


Setkeyboard::Setkeyboard()
{
    nr = 0;
	text = NULL;
	
	focus = 0;
}

Setkeyboard::~Setkeyboard()
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
	
	focus = 0;
}

DoubleKey Setkeyboard::addKey( int a, int b )
{
	DoubleKey doubleKey;
	doubleKey.a = a;
	doubleKey.b = b;
	
	return  doubleKey;
}

void Setkeyboard::load( int left, int right, int bot )
{
	nr = 22;
	text = new MyText[ nr ];
	
	for( int i = 0; i < nr; i++ )
	{
		text[ i ].setID( "keyboard-text nr " + std::to_string( i ) );
		text[ i ].setFont( "intro/Jaapokki-Regular.otf", 25, 0xFF, 0xFF, 0xFF );
	}
	
	text[ 0 ].setText( "Move left" );
	text[ 1 ].setText( "left" );
	text[ 2 ].setText( "Move right" );
	text[ 3 ].setText( "right" );
	
	text[ 4 ].setText( "Jump" );
	text[ 5 ].setText( "up" );
	
	text[ 6 ].setText( "Slide left" );
	text[ 7 ].setText( "down + left" );
	text[ 8 ].setText( "Slide right" );
	text[ 9 ].setText( "down + right" );
	
	text[ 10 ].setText( "Climb" );
	text[ 11 ].setText( "z + up" );
	text[ 12 ].setText( "Go down" );
	text[ 13 ].setText( "z + down" );
	
	text[ 14 ].setText( "Attack" );
	text[ 15 ].setText( "c" );
	text[ 16 ].setText( "Jump attack" );
	text[ 17 ].setText( "c + up" );
	
	text[ 18 ].setText( "Throw" );
	text[ 19 ].setText( "x" );
	text[ 20 ].setText( "Jump throw" );
	text[ 21 ].setText( "x + up" );
	
	
	text[ 0 ].setPosition( left, bot );
	text[ 1 ].setPosition( 250, bot );
	for( int i = 2; i < 10; i += 2 )
	{
		text[ i ].setPosition( left, text[ i -2 ].getBot() + 10 );
		text[ i +1 ].setPosition( 250, text[ i -2 ].getBot() + 10 );
	}
	
	text[ 10 ].setPosition( right +120, bot -5 );
	text[ 11 ].setPosition( right +350, bot -5 );
	for( int i = 12; i < nr -1; i += 2 )
	{
		text[ i ].setPosition( right +120, text[ i -2 ].getBot() + 10 );
		text[ i +1 ].setPosition( right +350, text[ i -2 ].getBot() + 10 );
	}
	

	keys.push_back( addKey( 71, -1 ) ); // right
	keys.push_back( addKey( 72, -1 ) ); // left
	
	keys.push_back( addKey( 73, -1 ) ); // up
	
	keys.push_back( addKey( 74, 71 ) ); // down + left
	keys.push_back( addKey( 74, 72 ) ); // down + right
	
	keys.push_back( addKey( 25, 73 ) ); // z + up
	keys.push_back( addKey( 25, 74 ) ); // z + down
	
	keys.push_back( addKey( 2, -1 ) ); // c
	keys.push_back( addKey( 2, 73 ) ); // c + up
	
	keys.push_back( addKey( 23, -1 ) ); // x
	keys.push_back( addKey( 23, 73 ) ); // x + up
	
	keys.push_back( addKey( 57, -1 ) ); // Escape
	keys.push_back( addKey( 1, -1 ) ); // b
	keys.push_back( addKey( 15, -1 ) ); // p
}


void Setkeyboard::draw( sf::RenderWindow &window )
{
	for( int i = 0; i < nr; i++ )
	{
		window.draw( text[ i ].get() );
	}
}
/*
void Setkeyboard::handle( sf::Event &event )
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
*/

void Setkeyboard::fadein( int j, int max )
{
	for( int i = 0; i < nr; i++ )
	{
		text[ i ].fadein( j, max );
	}
}

void Setkeyboard::fadeout( int j, int min )
{
	for( int i = 0; i < nr; i++ )
	{
		text[ i ].fadeout( j, min );
	}
}

/*
string* Setkeyboard::getHeroKeys()
{
 

	string* array = new string [ 4 ];
	
	for( int i = 0; i < nr; i ++ )
	{
		array[ i ] = to_string( keys[ i ] );
	}
	
	return array;
}
*/