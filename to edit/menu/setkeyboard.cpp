#include "setkeyboard.h"
#include <stdio.h>
#include <string>


Setkeyboard::Setkeyboard()
{
    nr = 0;
	text = NULL;
	
	focus = 0;
	which = -1;
	
	add = 0;
	remove = 0;
	addMode = 0;
	
	banNr = 0;
	bannedKeys = NULL;
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
	which = -1;
	
	add = 0;
	remove = 0;
	addMode = 0;
	
	if( bannedKeys != NULL )
	{
		delete [] bannedKeys;
		bannedKeys = NULL;
		banNr = 0;
	}
}

DoubleKey Setkeyboard::addKey( int a, int b )
{
	DoubleKey doubleKey;
	doubleKey.a = a;
	doubleKey.b = b;
	
	return  doubleKey;
}


string Setkeyboard::getName( int n )
{
	string name = "";
	
	if( n <= 25 )	// from A to Z
	{
		// in ASCII 97 means letter 'a'
		name = static_cast <char> ( n + 97 );
	}
	else
	{
		switch( n )
		{
			case 71: name = "left";	 	break;
			case 72: name = "right";	break;
			case 73: name = "up";		break;
			case 74: name = "down";		break;
			
			case 57: name = "space";	break;
			case 58: name = "return";	break;
			
			case 37: name = "l ctrl";	break;
			case 41: name = "r ctrl";	break;
			
			case 38: name = "l shift";	break;
			case 42: name = "r shift";	break;
			
			case 39: name = "l alt";	break;
			case 43: name = "r alt";	break;
		}
	}
	
	return name;
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
	

	keys.push_back( addKey( 71, -1 ) ); // left
	keys.push_back( addKey( 72, -1 ) ); // right
	
	keys.push_back( addKey( 73, -1 ) ); // up
	
	keys.push_back( addKey( 74, 71 ) ); // down + left
	keys.push_back( addKey( 74, 72 ) ); // down + right
	
	keys.push_back( addKey( 25, 73 ) ); // z + up
	keys.push_back( addKey( 25, 74 ) ); // z + down
	
	keys.push_back( addKey( 2, -1 ) ); // c
	keys.push_back( addKey( 2, 73 ) ); // c + up
	
	keys.push_back( addKey( 23, -1 ) ); // x
	keys.push_back( addKey( 23, 73 ) ); // x + up
	
	actual_keys = keys;
	
	add = 67;
	remove = 68;
	
	banNr = 4;
	bannedKeys = new int[ banNr ];
	bannedKeys[ 0 ] = 1;
	bannedKeys[ 1 ] = 15;
	bannedKeys[ 2 ] = 16;
	bannedKeys[ 3 ] = 36;
}


void Setkeyboard::draw( sf::RenderWindow &window )
{
	for( int i = 0; i < nr; i++ )
	{
		window.draw( text[ i ].get() );
	}
}

void Setkeyboard::handle( sf::Event &event )
{
	if( which != -1 )
	{
		static bool rel = false;
		
		if( event.type == sf::Event::KeyPressed && !rel )
		{
			if( addMode == 1 )
			{
				sf::Uint8 code = event.key.code;
				bool success = false;
				
				if( code > -1 && code <= 25 )
					success = true;
				else if( code >= 71 && code <= 74 )
					success = true;
				else if( code >= 37 && code <= 43 )
					success = true;
					
				for( int i = 0; i < banNr; i++ )
				{
					if( code == bannedKeys[ i ] )
					{
						success = false;
						break;
					}
				}
				
				if( success )
				{
					if( actual_keys[ which/2 ].a < 0 )
					{
						actual_keys[ which/2 ].a = event.key.code;
						text[ which +1 ].setText( getName( event.key.code ) );
						text[ which +1 ].reloadPosition();
					}
					else if( actual_keys[ which/2 ].b < 0 )
					{
						actual_keys[ which/2 ].b = event.key.code;
						text[ which +1 ].setText( getName( actual_keys[ which/2 ].a ) + " + " + getName( event.key.code ) );
						text[ which +1 ].reloadPosition();
					}
				}
			}
			
			if( event.key.code == remove ) // '-'
			{
				if( actual_keys[ which/2 ].b != -1 )
				{
					actual_keys[ which/2 ].b = -1;
				}
				else if( actual_keys[ which/2 ].a != -1 )
					actual_keys[ which/2 ].a = -1;
				
				
				if( actual_keys[ which/2 ].isEmpty() )
				{
					text[ which +1 ].setText( "-" );
					text[ which +1 ].reloadPosition();
				}
				else if( actual_keys[ which/2 ].a != -1 )
				{
					text[ which +1 ].setText( getName( actual_keys[ which/2 ].a ) );
					text[ which +1 ].reloadPosition();
				}
				
				
				// printf( "key nr %d, text nr %d\n", which/2, which +1 );
				
				text[ which ].setColor( 0x8C, 0x00, 0x1A );
				addMode = 0;
			}
			else if( event.key.code == add ) // '+'
			{
				if( actual_keys[ which/2 ].oneIsFree() )
				{
					addMode = 1;
					text[ which ].setColor( 0x8C, 0xA9, 0x3E );
				}
				else
				{
					addMode = 0;
				}
			}
			
			rel = true;
		}
		else if( event.type == sf::Event::KeyReleased )
		{
			rel = false;
		}
	}
	
	if( event.type == sf::Event::MouseButtonPressed )
	{
		for( unsigned i = 0; i < actual_keys.size(); i++ )
		{
			if( actual_keys[ i ].isEmpty() )
			{
				actual_keys[ i ] = keys[ i ];
				string newName = "";
				
				newName += getName( actual_keys[ i ].a );
					
				if( actual_keys[ i ].b > -1 )
					newName +=  " + " + getName( actual_keys[ i ].b );
				
				text[ i*2 +1 ].setText( newName );
				text[ i*2 +1 ].reloadPosition();
				
				// printf( "text nr %d\n", i*2 );
			}
		}
		
		which = -1;
		int x = event.mouseButton.x;
		int y = event.mouseButton.y;
		
		for( int i = 0; i < nr; i += 2 )
		{
			if( text[ i ].checkCollision( x, y, 0, 5 ) )
			{
				which = i;
				break;
			}
		}
		
		for( int i = 0; i < nr; i += 2 )
		{
			text[ i ].setColor( 0xFF, 0xFF, 0xFF );
		}
		
		if( which != -1 )
		{
			text[ which ].setColor( 0xFF, 0xDE, 0x00 );
		}
	}
}
/*
void Setkeyboard::handle( sf::Event &event )
{

	
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


vector <DoubleKey> Setkeyboard::getHeroKeys()
{
	return actual_keys;
}