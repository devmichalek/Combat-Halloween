/**
    nick_setter.h
    Purpose: class Nick_setter - set your own nick -mechanics.

    @author Adrian Michalek
    @version 2017.04.22
	@email adrmic98@gmail.com
*/

#include "nick_setter.h"
#include "file/file.h"

Nick_setter::Nick_setter()
{
	free();
}

Nick_setter::~Nick_setter()
{
	free();
}

void Nick_setter::free()
{
	text.free();
	label.free();
	
	min = max = 0;
	amount = 0;
	
	release = false;
	nick = "";
	
	next = false;
}



void Nick_setter::load( int w, int h )
{
	free();
	
	min = 3;
	max = 11;
	amount = 0;
	
	label.setName( "nick_setter-label" );
	label.load( "data/initialization/fancy_label.png" );
	
	text.setName( "nick_setter-text" );
	text.setFont( "data/initialization/Jaapokki-Regular.otf", 40, 0xFF, 0xFF, 0xFF );
	text.setText( "___________"  );
}

void Nick_setter::handle( sf::Event &event )
{
	// keyboard stuff
	if( label.getAlpha() == 0xFF && !next )
	{
		if( event.type == sf::Event::KeyPressed && !release )
		{
			// add key if we clicked key "+" before.
			if( isPossibleKey( event ) )
			{
				if( nick.size() < max )
				{
					nick += getName( event.key.code );
					text.setText( nick );
					reloadPosition();
				}
			}
			else if( event.key.code == 59 )	// backspace
			{
				// printf( "happen\n" );
				if( nick.size() > 1 )
				{
					string new_nick = "";
					for( unsigned i = 0; i < nick.size() -1; i++ )
					{
						new_nick += nick[ i ];
					}
					
					nick = new_nick;
					text.setText( nick );
					reloadPosition();
				}
				else if( nick.size() == 1 )
				{
					nick = "";
					text.setText( "___________" );
					reloadPosition();
				}
			}
			else if( event.key.code == 58 )	// enter, return
			{
				if( nick.size() >= min )
				{
					next = true;
					
					// Set "next".
					MyFile file;
					file.load( "data/txt/nick/nick_status.txt", std::ios::out );
					if( file.is_good() )
					{
						string line = "1";
						file.get() << line;
					}
					file.free();
					
					// Set "next".
					file.load( "data/txt/nick/nick_current.txt", std::ios::out );
					if( file.is_good() )
					{
						file.get() << nick;
					}
					file.free();
				}
			}
			
			release = true;
		}
		else if( event.type == sf::Event::KeyReleased )
		{
			release = false;
		}
	}
}

void Nick_setter::draw( sf::RenderWindow* &window )
{
	window->draw( label.get() );
	window->draw( text.get() );
}



void Nick_setter::fadein( int i, int max )
{
	text.fadein( i, max );
	label.fadein( i, max );
	
}

void Nick_setter::fadeout( int i, int min )
{
	text.fadeout( i, min );
	label.fadeout( i, min );
}



void Nick_setter::reloadPosition()
{
	text.setPosition( label.getX() +label.getWidth()/2 -text.getWidth() /2, label.getY() +(50*label.getYScale()) );
}

bool Nick_setter::isPossibleKey( sf::Event &event )
{
	sf::Uint8 code = event.key.code;
	
	if( code > -1 && code <= 35 )
	{
		return true;
	}
	else if( code >= 75 && code <= 84 )
	{
		return true;
	}

	return false;
}

string Nick_setter::getName( int n )
{
	string name = "";
	
	if( n > -1 && n <= 25 )	// from a to z
	{
		// in ASCII 97 means letter 'a'
		name = static_cast <char> ( n + 97 );
	}
	else if( n >= 26 && n <= 35 )
	{
		// 26 + 22 = 48
		// in ASCII 48 means character 0
		name = static_cast <char> ( n + 22 );
	}
	else if( n >= 75 && n <= 84 )
	{
		// 75 - 27 = 48
		// in ASCII 48 means character 0
		name = static_cast <char> ( n - 27 );
	}
	
	return name;
}

bool Nick_setter::nextState()
{
	return next;
}



void Nick_setter::setScale( float s_x, float s_y )
{
	label.setBasicScale( s_x, s_y );
	label.setScale();
	
	text.setBasicScale( s_x, s_y );
	text.setScale();
}

void Nick_setter::setView( int w, int h, int r_x, int r_y )
{
	label.setPosition( w /2 -label.getWidth() /2 +r_x, h /3 +label.getHeight() /2 +r_y );
	reloadPosition();
}