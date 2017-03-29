/**
    keyboard.h
    Purpose: class Keyboard and Key - to manage keyboard.

    @author Adrian Michalek
    @version 2016.11.11
	@email adrmic98@gmail.com
*/

#include "keyboard.h"
#include "file/file.h"


Key::Key(int one, int two )
{
	this->one = one;
	this->two = two;
}

Key::~Key()
{
	free();
}

void Key::free()
{
	one = two = -1;
}

bool Key::isEmpty()
{
	if( one == -1 && two == -1 )
	{
		return true;
	}
	
	return false;
}

bool Key::oneIsFree()
{
	if( one == -1 || two == -1 )
	{
		return true;
	}
	
	return false;
}



Keyboard::Keyboard()
{
	focus = false;
	which = -1;
	
	addMode = false;
	release = false;
	lastChosen = -1;
}

Keyboard::~Keyboard()
{
	free();
}

void Keyboard::free()
{
	save_button.free();
	
	freeObject( text );
	freeObject( keys );
	freeObject( actual_keys );
	if( !banned_keys.empty() )
	{
		banned_keys.clear();
	}
	
	focus = false;
	which = -1;
	
	addMode = false;
	release = false;
	lastChosen = -1;
}

template <typename object>
void Keyboard::freeObject( vector <object> o )
{
	if( !o.empty() )
	{
		for( auto &it :o )
		{
			it->free();
		}

		o.clear();
	}
}




void Keyboard::load( int left, int right, int bot, int screen_w, int screen_h )
{
	// button
	save_button.setName( "keyboard-save_button" );
	save_button.load( "data/02_menu/save.png", 4 );
	save_button.setScale( 0.5, 0.5 );
	save_button.setPosition( screen_w - save_button.getWidth() -30, screen_h/2 -80 );
	
	// text
	for( int i = 0; i < 18; i++ )
	{
		text.push_back( new MyText() );
		text[ i ]->setName( "keyboard-text nr " + con::itos( i ) );
		text[ i ]->setFont( "data/00_loading/Jaapokki-Regular.otf", 25, 0xFF, 0xFF, 0xFF );
	}

	// load default keys
	MyFile file;
	file.load( "data/txt/keyboard/keyboard_default.txt" );
	if( file.is_good() )
	{
		int a = -2, b = -2;
		string buf;
		while( file.get() >> buf )
		{
			if( a != -2 )
			{
				b = con::stoi( buf );
				keys.push_back( new Key( a, b ) );
				a = -2;
			}
			else
				a = con::stoi( buf );
		}
	}
	file.free();
	
	// load temporary keys
	file.load( "data/txt/keyboard/keyboard_temporary.txt" );
	if( file.is_good() )
	{
		int a = -2, b = -2;
		string buf;
		while( file.get() >> buf )
		{
			if( a != -2 )
			{
				b = con::stoi( buf );
				actual_keys.push_back( new Key( a, b ) );
				a = -2;
			}
			else
				a = con::stoi( buf );
		}
		
		for( unsigned i = 1; i < text.size(); i += 2 )
		{
			string newName = "";
			
			newName += getName( actual_keys[ (i-1) / 2 ]->one );
			
			if( actual_keys[ (i-1) / 2 ]->two != -1 )
			{
				newName += " + " + getName( actual_keys[ (i-1) / 2 ]->two );
			}
			
			text[ i ]->setText( newName );
		}
	}
	file.free();
	
	
	// set text
	text[ 0 ]->setText( "Move left" );
	text[ 2 ]->setText( "Move right" );
	text[ 4 ]->setText( "Jump" );
	text[ 6 ]->setText( "Slide" );
	text[ 8 ]->setText( "Climb" );
	text[ 10 ]->setText( "Attack" );
	text[ 12 ]->setText( "Jump attack" );
	text[ 14 ]->setText( "Throw" );
	text[ 16 ]->setText( "Jump throw" );
	
	// set position
	text[ 0 ]->setPosition( left, bot );
	text[ 1 ]->setPosition( 250, bot );
	for( int i = 2; i < 8; i += 2 )
	{
		text[ i ]->setPosition( left, text[ i -2 ]->getBot() + 10 );
		text[ i +1 ]->setPosition( 250, text[ i -2 ]->getBot() + 10 );
	}
	
	text[ 8 ]->setPosition( right +120, bot -5 );
	text[ 9 ]->setPosition( right +350, bot -5 );
	for( unsigned i = 10; i < text.size() -1; i += 2 )
	{
		text[ i ]->setPosition( right +120, text[ i -2 ]->getBot() + 10 );
		text[ i +1 ]->setPosition( right +350, text[ i -2 ]->getBot() + 10 );
	}
	
	
	// load and set banned keys
	file.load( "data/txt/keyboard/banned_keys.txt" );
	if( file.is_good() )
	{
		string buf;
		while( file.get() >> buf )
		{
			banned_keys.push_back( con::stoi( buf ) );
		}
	}
	file.free();
	
	click.setID( "keyboard-click" );
	click.load( "data/02_menu/click.wav", 50 );
}

void Keyboard::draw( sf::RenderWindow &window )
{
	for( vector <MyText*>::iterator it = text.begin(); it != text.end(); it++ )
	{
		window.draw( (*it)->get() );
	}
	
	window.draw( save_button.get() );
}

void Keyboard::handle( sf::Event &event )
{
	// keyboard stuff
	if( which != -1 )
	{
		if( event.type == sf::Event::KeyPressed && !release )
		{
			// add key if we clicked key "+" before.
			if( isPossibleKey( event ) && addMode )
			{
				if( actual_keys[ which/2 ]->one < 0 )
				{
					actual_keys[ which/2 ]->one = event.key.code;
					text[ which +1 ]->setText( getName( event.key.code ) );
				}
				else if( actual_keys[ which/2 ]->two < 0 )
				{
					actual_keys[ which/2 ]->two = event.key.code;
					text[ which +1 ]->setText( getName( actual_keys[ which/2 ]->one ) + " + " + getName( event.key.code ) );
				}
				
				text[ which +1 ]->reloadPosition();
			}
			
			// check if we clicked key "-"
			if( !substract( event ) )
			{
				// check if we clicked key "+" if yes then allow ( set addMode = true )
				add( event );
			}
			
			release = true;
		}
		else if( event.type == sf::Event::KeyReleased )
		{
			release = false;
		}
	}
	
	
	// mouse stuff
	if( event.type == sf::Event::MouseButtonPressed )
	{
		// check whether key is empty
		for( unsigned i = 0; i < actual_keys.size(); i++ )
		{
			if( actual_keys[ i ]->isEmpty() )
			{
				int one = keys[ i ]->one;
				actual_keys[ i ]->one = one;
				
				text[ i*2 +1 ]->setText( getName( actual_keys[ i ]->one ) );
				text[ i*2 +1 ]->reloadPosition();
				// printf( "%s\n", getName( actual_keys[ i ]->one ).c_str() );
			}
		}
		
		
		int x = event.mouseButton.x;
		int y = event.mouseButton.y;
		
		// check if we have the same keys
		if( lastChosen != -1 )
		{
			bool error = false;

			for( unsigned i = 0; i < actual_keys.size(); i++ )
			{
				if( static_cast <unsigned> (lastChosen) == i )
				{
					continue;
				}
				else if( actual_keys[ lastChosen ]->one == actual_keys[ i ]->one && actual_keys[ lastChosen ]->two == actual_keys[ i ]->two )
				{
					error = true;
					break;
				}
				else if( actual_keys[ lastChosen ]->one == actual_keys[ i ]->two && actual_keys[ lastChosen ]->two == actual_keys[ i ]->one )
				{
					error = true;
					break;
				}
			}
			
			if( actual_keys[ lastChosen ]->one == actual_keys[ lastChosen ]->two )
			{
				error = true;
			}
			
			if( error )
			{
				actual_keys[ lastChosen ] = keys[ lastChosen ];
				
				string newName = "";
				
				newName += getName( actual_keys[ lastChosen ]->one );
				
				if( actual_keys[ lastChosen ]->two > -1 )
				{
					newName +=  " + " + getName( actual_keys[ lastChosen ]->two );
				}
					
				
				text[ lastChosen *2 +1 ]->setText( newName );
				text[ lastChosen *2 +1 ]->reloadPosition();
			}
			
			lastChosen = -1;
		}
		
		which = -1;
		for( unsigned i = 0; i < text.size(); i += 2 )
		{
			if( text[ i ]->checkCollision( x, y, 0, 5 ) )
			{
				which = i;
				lastChosen = which/2;
				break;
			}
		}
		
		
		for( unsigned i = 0; i < text.size(); i += 2 )
		{
			text[ i ]->setColor( 0xFF, 0xFF, 0xFF );
		}
		
		if( which != -1 )
		{
			text[ which ]->setColor( 0xFF, 0xDE, 0x00 );
		}
	}
	
	handleButton( event );
}



void Keyboard::fadein( int j, int max )
{
	for( auto &it :text )
	{
		it->fadein( j, max );
	}
	
	save_button.fadein( j, max );
}

void Keyboard::fadeout( int j, int min )
{
	for( auto &it :text )
	{
		it->fadeout( j, min );
	}
	
	save_button.fadeout( j, min );
}





string Keyboard::getName( int n )
{
	string name = "";
	
	if( n >= 0 && n <= 25 )	// from A to Z
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



void Keyboard::add( sf::Event &event )
{
	if( event.key.code == 67 ) // '+'
	{
		if( actual_keys[ which/2 ]->oneIsFree() )
		{
			addMode = true;
			text[ which ]->setColor( 0x8C, 0xA9, 0x3E );	// green
		}
		else
		{
			addMode = false;
		}
	}
}

bool Keyboard::substract( sf::Event &event )
{
	if( event.key.code == 68 ) // '-'
	{
		if( actual_keys[ which/2 ]->two != -1 )
		{
			actual_keys[ which/2 ]->two = -1;
		}
		else if( actual_keys[ which/2 ]->one != -1 )
		{
			actual_keys[ which/2 ]->one = -1;
		}
		
		
		if( actual_keys[ which/2 ]->isEmpty() )
		{
			text[ which +1 ]->setText( "-" );
			text[ which +1 ]->reloadPosition();
		}
		else
		{
			text[ which +1 ]->setText( getName( actual_keys[ which/2 ]->one ) );
			text[ which +1 ]->reloadPosition();
		}
		
		
		// printf( "key nr %d, text nr %d\n", which/2, which +1 );
		
		text[ which ]->setColor( 0x8C, 0x00, 0x1A );	// red
		addMode = false;
		
		return true;
	}
	
	return false;
}

bool Keyboard::isPossibleKey( sf::Event &event )
{
	sf::Uint8 code = event.key.code;
	
	bool success = true;
	for( unsigned i = 0; i < banned_keys.size(); i++ )
	{
		if( code == banned_keys[ i ] )
		{
			success = false;
			break;
		}
	}
	
	if( success )
	{
		if( code > -1 && code <= 25 )
		{
			return true;
		}
		else if( code >= 71 && code <= 74 )
		{
			return true;
		}
		else if( code >= 37 && code <= 43 )
		{
			return true;
		}
		else if( code == 57 || code == 58 )
		{
			return true;
		}
	}

	return false;
}

void Keyboard::handleButton( sf::Event &event )
{
	save_button.setOffset( 0 );
	
	if( event.type == sf::Event::MouseButtonPressed )
	{
		int x = event.mouseButton.x;
		int y = event.mouseButton.y;
		
		if( save_button.checkCollision( x, y ) )
		{
			MyFile file;
			file.load( "data/txt/keyboard/keyboard_temporary.txt", std::ios::out );
			printf( "happend\n" );
			for( unsigned i = 0; i < actual_keys.size(); i++ )
			{
				file.get() << con::itos( actual_keys[ i ]->one ) + "\n";
				file.get() << con::itos( actual_keys[ i ]->two ) + "\n";
			}
			file.free();
			
			save_button.setOffset( 2 );
			focus = true;
			
			if( play )
			{
				click.play();
			}
		}
	}
	else if( event.type == sf::Event::MouseMoved )
	{
		int x = event.mouseMove.x;
		int y = event.mouseMove.y;
		
		if( save_button.checkCollision( x, y ) )
		{
			save_button.setOffset( 1 );
		}
		else
		{
			focus = false;
		}
	}
	else if( event.type == sf::Event::MouseButtonReleased )
	{
		focus = false;
	}
		
	if( focus )
	{
		save_button.setOffset( 2 );
	}
}