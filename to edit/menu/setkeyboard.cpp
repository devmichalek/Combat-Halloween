#include "setkeyboard.h"
#include <stdio.h>
#include <string>
#include <fstream>

int Setkeyboard::strToInt(string s)
{
    bool m=false;
    int tmp=0;
    unsigned i=0;
    if(s[0]=='-')
    {
          i++;
          m = true;
    }
	
    while(i<s.size())
    {
      tmp = 10*tmp+s[i]-48;
      i++;
    }
	
    return m ? -tmp : tmp;   
}


Setkeyboard::Setkeyboard()
{
    nr = 0;
	text = NULL;
	
	focus = false;
	which = -1;
	
	add = 0;
	remove = 0;
	addMode = 0;
	
	banNr = 0;
	bannedKeys = NULL;
	save.free();
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
	
	focus = false;
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

void Setkeyboard::loadButton( int screen_w, int screen_h )
{
	save.setName( "setkeyboard-save" );
	save.load( "data/sprites/menu/save.png", 4 );
	save.setScale( 0.5, 0.5 );
	save.setPosition( screen_w - save.getWidth() -30, screen_h/2 -80 );
}

void Setkeyboard::load( int left, int right, int bot )
{
	nr = 20;
	text = new MyText[ nr ];
	
	for( int i = 0; i < nr; i++ )
	{
		text[ i ].setID( "keyboard-text nr " + std::to_string( i ) );
		text[ i ].setFont( "data/fonts/Jaapokki-Regular.otf", 25, 0xFF, 0xFF, 0xFF );
	}

	// load default keys
	fstream file;
	
	file.open( "data/txt/menu/keyboard_default.txt" );
	if( file.bad() )
	{
		printf( "Can not load %s\n", "data/txt/menu/keyboard_default.txt" );
	}
	else
	{
		// printf( "something" );
		int a = -2, b = -2;
		string buf;
		while( file >> buf )
		{
			if( a != -2 )
			{
				b = strToInt( buf );
				keys.push_back( addKey( a, b ) );
				a = -2;
			}
			else
				a = strToInt( buf );
		}
	}
	file.close();
	
	// load temporary keys
	file.open( "data/txt/menu/keyboard_temporary.txt" );
	if( file.bad() )
	{
		printf( "Can not load %s\n", "data/txt/menu/keyboard_temporary.txt" );
	}
	else
	{
		// printf( "something" );
		int a = -2, b = -2;
		string buf;
		while( file >> buf )
		{
			if( a != -2 )
			{
				b = strToInt( buf );
				actual_keys.push_back( addKey( a, b ) );
				a = -2;
			}
			else
				a = strToInt( buf );
		}
		
		for( int i = 1; i < nr; i += 2 )
		{
			string newName = "";
			newName += getName( actual_keys[ (i-1) / 2 ].a );
			if( actual_keys[ (i-1) / 2 ].b != -1 )
				newName += " + " + getName( actual_keys[ (i-1) / 2 ].b );
				
			text[ i ].setText( newName );
		}
	}
	file.close();
	
	
	
	text[ 0 ].setText( "Move left" );
	text[ 2 ].setText( "Move right" );
	
	text[ 4 ].setText( "Jump" );
	
	text[ 6 ].setText( "Slide" );
	
	text[ 8 ].setText( "Climb" );
	text[ 10 ].setText( "Go down" );
	
	text[ 12 ].setText( "Attack" );
	text[ 14 ].setText( "Jump attack" );
	
	text[ 16 ].setText( "Throw" );
	text[ 18 ].setText( "Jump throw" );
	
	
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
	
	add = 67;
	remove = 68;
	
	banNr = 4;
	bannedKeys = new int[ banNr ];
	bannedKeys[ 0 ] = 1;
	bannedKeys[ 1 ] = 15;
	bannedKeys[ 2 ] = 16;
	bannedKeys[ 3 ] = 36;
	
	click.setID( "setkeyboard-click" );
	click.load( "data/sounds//click.wav", 50 );
}


void Setkeyboard::draw( sf::RenderWindow &window )
{
	for( int i = 0; i < nr; i++ )
	{
		window.draw( text[ i ].get() );
	}
	
	window.draw( save.get() );
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
	
	save.setOffset( 0 );
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
		
		if( save.checkCollision( x, y ) )
		{
			fstream file;
			file.open( "data/txt/menu/keyboard_temporary.txt", std::ios::out );
			
			for( unsigned i = 0; i < actual_keys.size(); i++ )
			{
				file << to_string( actual_keys[ i ].a ) + "\n";
				file << to_string( actual_keys[ i ].b ) + "\n";
			}
			save.setOffset( 2 );
			focus = true;
			
			if( play )
				click.play();
		}
	}
	else if( event.type == sf::Event::MouseMoved )
	{
		int x = event.mouseMove.x;
		int y = event.mouseMove.y;
		if( save.checkCollision( x, y ) )
			save.setOffset( 1 );
		else
			focus = false;
	}
	else if( event.type == sf::Event::MouseButtonReleased )
		focus = false;
		
	if( focus )
		save.setOffset( 2 );
}

void Setkeyboard::fadein( int j, int max )
{
	for( int i = 0; i < nr; i++ )
	{
		text[ i ].fadein( j, max );
	}
	
	save.fadein( j, max );
}

void Setkeyboard::fadeout( int j, int min )
{
	for( int i = 0; i < nr; i++ )
	{
		text[ i ].fadeout( j, min );
	}
	
	save.fadeout( j, min );
}


vector <DoubleKey> Setkeyboard::getHeroKeys()
{
	return actual_keys;
}