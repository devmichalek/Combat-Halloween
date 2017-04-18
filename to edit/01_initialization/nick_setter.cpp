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
	label.free();
	text.free();
	y_state = 0;
	
	min = max = 0;
	amount = 0;
	
	release = false;
	nick = "";
	next = false;
}



void Nick_setter::load( int screen_w, int screen_h )
{
	free();
	
	label.setName( "nick_setter-label" );
	label.load( "data/01_initialization/fancy_label.png" );
	label.setPosition( screen_w /2 -label.getWidth() /2, screen_h /3 +label.getHeight() /2 );
	
	y_state = 345;
	text.setName( "nick_setter-text" );
	text.setFont( "data/00_loading/Jaapokki-Regular.otf", 40, 0xFF, 0xFF, 0xFF );
	text.setText( "___________"  );
	reloadPosition();
	
	min = 3;
	max = 11;
	amount = 0;
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



void Nick_setter::reloadPosition()
{
	text.setPosition( label.getX() +label.getWidth()/2 -text.getWidth() /2, y_state );
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



void Nick_setter::fadein( int i, int max )
{
	label.fadein( i, max );
	text.fadein( i, max );
}

void Nick_setter::fadeout( int i, int min )
{
	label.fadeout( i, min );
	text.fadeout( i, min );
}
