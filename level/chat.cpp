#include "chat.h"
#include "own/file.h"

Chat::Chat()
{
	free();
}

Chat::~Chat()
{
	free();
}

void Chat::free()
{
	screen_w = 0;
	screen_h = 0;
	open = false;
	capslock = 0;
	shift = 0;
	used = false;
	
	background.free();
	second_background.free();
	text_background.free();
	
	if( !text_ys.empty() )
	{
		text_ys.clear();
	}
	
	if( !writtenStrs.empty() )
	{
		writtenStrs.clear();
	}
	
	username.free();
	
	if( !writtens.empty() )
	{
		writtens.clear();
		for( auto &it :writtens )
		{
			it->free();
			delete it;
			it = NULL;
		}
	}
	
	line = 1;
	counter = 0;
	arrow.free();
}

void Chat::load( float screen_w, float screen_h )
{
	free();
	
	srand( static_cast <int> ( time( NULL ) ) );
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	// ( "fonts/jcandlestickextracond.ttf" );
	// ( "fonts/Jaapokki-Regular.otf" );
	
	// Set writtens.
	int how_many = 10;
	for( int i = 0; i < how_many -1; i++ )
	{
		writtens.push_back( new MyText() );
		writtens[ i ]->setIdentity( "chat-writtens" );
		writtens[ i ]->setFont( "fonts/Jaapokki-Regular.otf" );
		writtens[ i ]->setText( "gT" );
		writtens[ i ]->setSize( screen_h /36 );
		writtens[ i ]->setAlpha( 0xFF );
		text_ys.push_back( screen_h -(writtens[ i ]->getHeight() +screen_h /72) *(i +1) );
		writtenStrs.push_back( "" );
	}
	
	
	// Set background.
	background.setIdentity( "chat-background" );
	background.create( screen_w /3 *2, (writtens[ 0 ]->getHeight() +screen_h /72) *how_many );
	background.setColor( sf::Color( 0, 0, 0 ) );
	background.setPosition( 0, screen_h -((writtens[ 0 ]->getHeight() +screen_h /72) *how_many) );
	background.setAlpha( 0xFF /10 );
	
	// Set second bacground.
	second_background.setIdentity( "chat-second_background" );
	second_background.create( screen_w /3 *2, writtens[ 0 ]->getHeight() +screen_h /72 );
	second_background.setColor( sf::Color( 0x00, 0x00, 0x00 ) );
	second_background.setPosition( 0, screen_h -(writtens[ 0 ]->getHeight() +screen_h /72) );
	second_background.setAlpha( 0xFF /5 );
	
	// Set text bacground.
	text_background.setIdentity( "chat-text_background" );
	text_background.setFont( "fonts/Jaapokki-Regular.otf" );
	text_background.setText( "Esc" );
	text_background.setSize( screen_h /36 );
	// text_background.setColor( sf::Color( 0xDD, 0xDD, 0xDD ) );
	text_background.setAlpha( 0xFF );
	text_background.setPosition( background.getX(), background.getY() );
	
	//Set arrow.
	arrow.setIdentity( "chat-arrow" );
	arrow.setFont( "fonts/Jaapokki-Regular.otf" );
	arrow.setText( "|" );
	arrow.setSize( screen_h /36 );
	arrow.setAlpha( 0xFF );
	
	// Set username and the rest.
	username.setIdentity( "chat-username" );
	username.setFont( "fonts/Jaapokki-Regular.otf" );
	setUsername( "error" );
}

void Chat::handle( sf::Event& event )
{
	if( open )
	{
		if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) )
		{
			if( text_background.checkCollision( event.mouseButton.x, event.mouseButton.y ) )
			{
				open = false;
			}
		}
		
		if( event.type == sf::Event::KeyPressed )
		{
			used = false;
			
			// Backspace.
			if( event.key.code == 59 )
			{
				if( writtenStrs[ 0 ].size() > 0 )
				{
					writtenStrs[ 0 ].pop_back();
					setWritten();
				}
			}
			
			// Enter, return.
			else if( event.key.code == 58 && writtenStrs[ 0 ] != "" )
			{
				for( unsigned i = writtenStrs.size() -1; i >= 1 ; i-- )
				{
					writtenStrs[ i ] = writtenStrs[ i -1 ];
				}
				writtenStrs[ 0 ] = "";
				setWritten();
				
				if( writtenStrs[ 1 ][ 0 ] == '@' )
				{
					used = true;
				}
			}
			
			// Shift
			else if( event.key.code == 38 || event.key.code == 42 )
			{
				shift = -32;
			}
			
			// Esc.
			else if( event.key.code == 36 )
			{
				open = !open;
			}
			
			// CapsLock
			else if( event.key.code == -1 )
			{
				if( capslock < 0 )
				{
					capslock = 0;
				}
				else
				{
					capslock = -32;
				}
			}
			
			// The rest.
			else if( arrow.getRight() +username.getWidth() +screen_w /128 < screen_w /3 *2 )
			{
				// printf( "%d\n", event.key.code );
				if( getChar( event.key.code ) != NULL )
				{
					writtenStrs[ 0 ] += *getChar( event.key.code );
					setWritten();
				}
			}
		}
		else if( event.type == sf::Event::KeyReleased )
		{
			if( event.key.code == 38 || event.key.code == 42 )
			{
				shift = 0;
			}
		}
	}
	else
	{
		if( event.type == sf::Event::KeyPressed )
		{
			// 'o'
			if( event.key.code == 14 )
			{
				open = !open;
			}
		}
	}
}

void Chat::draw( sf::RenderWindow* &window )
{
	if( open )
	{
		window->draw( background.get() );
		window->draw( second_background.get() );
		window->draw( text_background.get() );
		
		for( unsigned i = 0; i < writtens.size(); i++ )
		{
			if( writtenStrs[ i ] != "" && i != 0 )
			{
				username.setPosition( screen_w /256, writtens[ i ]->getY() );
				window->draw( username.get() );
			}
			
			window->draw( writtens[ i ]->get() );
		}
		
		// draw arrow.
		if( counter < line /2 )
		{
			window->draw( arrow.get() );
		}
	}
}

void Chat::mechanics( double elapsedTime )
{
	counter += elapsedTime;
	if( counter > line )
	{
		counter = 0;
	}
}



bool& Chat::isOpen()
{
	return open;
}

bool Chat::isUsed()
{
	if( open && used )
	{
		return true;
	}
	
	return false;
}

char* Chat::getChar( int n )
{
	bool success = false;
	char result = ' ';
	
	// letters
	if( n >= 0 && n <= 25 )
	{
		int buf = 0;
		if( capslock < 0 || shift < 0 )
		{
			buf = -32;
		}
		result = static_cast <char> (n +97 +buf);
		success = true;
	}
	
	// special
	else if( shift < 0 )
	{
		success = true;
		switch( n )
		{
			// 1 ... 9
			case 26: result = ')'; break;
			case 27: result = '!'; break;
			case 28: result = '@'; break;
			case 29: result = '#'; break;
			case 30: result = '$'; break;
			case 31: result = '%'; break;
			case 32: result = '^'; break;
			case 33: result = '&'; break;
			case 34: result = '*'; break;
			case 35: result = '('; break;
			
			// the rest
			case 46: result = '{'; break;
			case 47: result = '}'; break;
			case 48: result = ':'; break;
			case 49: result = '<'; break;
			case 50: result = '>'; break;
			case 51: result = '"'; break;
			case 52: result = '?'; break;
			case 55: result = '+'; break;
			case 56: result = '_'; break;
			
			default: success = false; break;
		}
	}
	
	// numbers
	else if( n >= 26 && n <= 35 )
	{
		result = static_cast <char> (n +22);
		success = true;
	}
	else if( n >= 75 && n <= 84 )
	{
		result = static_cast <char> (n -27);
		success = true;
	}
	
	else
	{
		success = true;
		switch( n )
		{
			case 46: result = '['; break;
			case 47: result = ']'; break;
			case 48: result = ';'; break;
			case 49: result = ','; break;
			case 50: result = '.'; break;
			case 51: result = static_cast <char> (39); break; // '
			case 52: result = '/'; break;
			case 55: result = '='; break;
			case 56: result = '-'; break;
			case 57: result = ' '; break;
			
			case 67: result = '+'; break;
			case 68: result = '-'; break;
			case 69: result = '*'; break;
			case 70: result = '/'; break;
			
			default: success = false; break;
		}
	}
	
	if( !success )
	{
		return NULL;
	}
	
	char* r = NULL;
	r = new char( result );
	
	return r;
}

bool Chat::getCommand( string command )
{
	if( writtenStrs[ 1 ] == command )
	{
		used = false;
		return true;
	}
	
	return false;
}



void Chat::setUsername( string line )
{
	// Set username.
	username.setText( line +": " );
	username.setSize( screen_h /36 );
	username.setColor( sf::Color( 0xF2, 0x58, 0x3E ) );
	username.setAlpha( 0xFF );
	
	setWritten();
}

void Chat::setWritten()
{
	for( unsigned i = 0; i < writtens.size(); i++ )
	{
		writtens[ i ]->setText( writtenStrs[ i ] );
		writtens[ i ]->setPosition( username.getRight() +screen_w /256, text_ys[ i ] );
		
		if( writtenStrs[ i ][ 0 ] == '@' )
		{
			writtens[ i ]->setColor( sf::Color( 0x00, 0x00, 0x00 ) );
		}
		else
		{
			writtens[ i ]->setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
		}
	}
	
	if( writtenStrs[ 0 ].size() == 0 )
	{
		writtens[ 0 ]->setText( " " );
	}
	else
	{
		writtens[ 0 ]->setText( writtenStrs[ 0 ] );
	}
	
	writtens[ 0 ]->setPosition( screen_w /256, text_ys[ 0 ] );
	
	if( writtenStrs[ 0 ].size() == 0 )
	{
		arrow.setPosition( 0, text_ys[ 0 ] );
	}
	else
	{
		arrow.setPosition( writtens[ 0 ]->getRight(), text_ys[ 0 ] );
	}
}