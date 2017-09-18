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
	commandColor = sf::Color( 0xFF, 0xFF, 0xFF );
	typicalColor = sf::Color( 0, 0, 0 );
	
	globalYScale = 0;
	globalYLine = 2;
	
	screen_w = 0;
	screen_h = 0;
	scale_x = 0;
	scale_y = 0;
	
	open = false;
	used = false;
	
	escButton.free();
	background.free();
	
	
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
	
	if( !writtenStrs.empty() )
	{
		writtenStrs.clear();
	}
	
	
	line = 1;
	counter = 0;
	arrow.free();
}

void Chat::reset()
{
	globalYScale = 0;
	
	for( auto &it :writtenStrs )
	{
		it = "";
	}
	
	setWritten();
	
	for( auto &it :writtens )
	{
		it->setAlpha( 0 );
	}
	
	escButton.setAlpha( 0 );
	background.setAlpha( 0 );
	arrow.setAlpha( 0 );
	username.setAlpha( 0 );
}



void Chat::load( float screen_w, float screen_h, bool white )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	float fontSize = screen_h /36;
	scale_x = screen_w /2560;
	scale_y = screen_h /1440;
	if( white )
	{
		fontSize = 20;
		scale_x = 0.5;
		scale_y = 0.5;
	}
	
	// Set writtens.
	for( int i = 0; i < 6; i++ )
	{
		writtens.push_back( new MyText() );
		writtens[ i ]->setIdentity( "chat-writtens" );
		writtens[ i ]->setFont( "fonts/Jaapokki-Regular.otf" );
		writtens[ i ]->setText( " " );
		writtens[ i ]->setSize( fontSize );
		writtens[ i ]->setAlpha( 0 );
		writtenStrs.push_back( "" );
	}
	
	// Set text bacground.
	escButton.setIdentity( "chat-escButton" );
	escButton.setFont( "fonts/Jaapokki-Regular.otf" );
	escButton.setText( "X" );
	escButton.setSize( fontSize );
	escButton.setColor( sf::Color::White );
	escButton.setAlpha( 0 );
	
	// Set background.
	background.setIdentity( "chat-background" );
	if( white )	background.load( "images/level/chat_white.png" );
	else		background.load( "images/level/chat.png" );
	background.setScale( scale_x, scale_y );
	background.setPosition( 0, screen_h -background.getHeight() );
	escButton.setPosition( background.getRight() -escButton.getWidth() -screen_w /192, background.getY() +screen_h /214 );
	background.setAlpha( 0 );
	
	//Set arrow.
	arrow.setIdentity( "chat-arrow" );
	arrow.setFont( "fonts/Jaapokki-Regular.otf" );
	arrow.setText( "|" );
	arrow.setSize( fontSize );
	arrow.setAlpha( 0 );
	
	// Set username and the rest.
	username.setIdentity( "chat-username" );
	username.setFont( "fonts/Jaapokki-Regular.otf" );
	setUsername( "error" );	// Just in case.
	username.setSize( fontSize );
	username.setColor( sf::Color( 0xF2, 0x58, 0x3E ) );
	username.setAlpha( 0 );
	username.setPosition( screen_w /256, 0 );
	
	escButton.setScale( 1, 1 *globalYScale /globalYLine );
	background.setScale( scale_x, scale_y *globalYScale /globalYLine );
	username.setScale( 1, 1 *globalYScale /globalYLine );
	
	for( auto &it :writtens )
	{
		it->setScale( 1, 1 *globalYScale /globalYLine );
	}
}

void Chat::handle( sf::Event& event )
{
	if( open )
	{
		if( globalYScale == globalYLine )
		{
			if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) )
			{
				if( escButton.checkCollision( event.mouseButton.x, event.mouseButton.y ) )
				{
					open = false;
				}
			}
			
			if( event.type == sf::Event::TextEntered )
			{
				if( event.text.unicode < 128 && event.text.unicode > 31 )
				{
					writtenStrs[ 0 ] += event.text.unicode;
					setWritten();
				}
			}
			
			if( event.type == sf::Event::KeyPressed )
			{
				used = false;
				
				// BackSpace
				if( event.key.code == sf::Keyboard::BackSpace )
				{
					if( writtenStrs[ 0 ].size() > 0 )
					{
						writtenStrs[ 0 ].pop_back();
						setWritten();
					}
				}
				
				// Enter, return.
				else if( event.key.code == sf::Keyboard::Return && writtenStrs[ 0 ].size() > 0 )
				{
					for( unsigned i = 0; i < writtenStrs[ 0 ].size(); i++ )
					{
						// printf( "1. ->%s<-\n", writtenStrs[ 0 ].c_str() );
						if( writtenStrs[ 0 ][ i ] == ' ' )
						{
							writtenStrs[ 0 ].erase( i, 1 );
							i --;
						}
						else
						{
							break;
						}
					}
					
					if( writtenStrs[ 0 ].size() > 0 )
					{
						for( int i = writtenStrs[ 0 ].size() -1; i >= 0 ; i-- )
						{
							// printf( "2. ->%s<-\n", writtenStrs[ 0 ].c_str() );
							if( writtenStrs[ 0 ][ i ] == ' ' )
							{
								writtenStrs[ 0 ].erase( i, 1 );
							}
							else
							{
								break;
							}
						}
					}
					
					if( writtenStrs[ 0 ].size() > 0 )
					{
						// Add \n if needed.
						string teststring = "";
						for( unsigned i = 0; i < writtenStrs[ 0 ].size(); i++ )
						{
							teststring += writtenStrs[ 0 ][ i ];
							writtens[ 0 ]->setText( teststring );
							
							if( writtens[ 0 ]->getWidth() +username.getWidth() +screen_w /64 >= background.getRight() )
							{
								string nextnewstring = "";
								for( unsigned j = 0; j < teststring.size() -1; j++ )
								{
									nextnewstring += teststring[ j ];
								}
								nextnewstring += "\n";
								nextnewstring += teststring[ teststring.size() -1 ];
								teststring = nextnewstring;
							}
						}
						
						writtenStrs[ 0 ] = teststring;
						
						for( unsigned i = writtenStrs.size() -1; i >= 1 ; i-- )
						{
							writtenStrs[ i ] = writtenStrs[ i -1 ];
						}
						
						writtenStrs[ 0 ] = "";
						
						
						if( writtens[ 0 ]->getRight() > background.getRight() )
						{
							
						}
						
						setWritten();
						
						if( writtenStrs[ 1 ][ 0 ] == '@' )
						{
							used = true;
						}
					}
					else 
					{
						setWritten();
					}
				}
				
				// Esc.
				else if( event.key.code == sf::Keyboard::Escape )
				{
					open = !open;
				}
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
				globalYScale = 0.1;
			}
		}
	}
}

void Chat::draw( sf::RenderWindow* &window )
{
	window->draw( background.get() );
	
	for( unsigned i = 0; i < writtens.size(); i++ )
	{
		if( writtens[ i ]->getY() >= background.getY() )
		{
			if( writtenStrs[ i ] != "" && i != 0 )
			{
				username.setPosition( screen_w /256, writtens[ i ]->getY() );
				window->draw( username.get() );
			}
			
			window->draw( writtens[ i ]->get() );
		}
	}
	
	// draw arrow.
	if( counter < line /2 )
	{
		window->draw( arrow.get() );
	}
	
	window->draw( escButton.get() );
}

void Chat::mechanics( double elapsedTime )
{
	counter += elapsedTime;
	if( counter > line )
	{
		counter = 0;
	}
	
	if( open )
	{
		float value = elapsedTime *0xFF *2;
		escButton.fadein( value );
		background.fadein( value );
		username.fadein( value );
		arrow.fadein( value );
		for( auto &it :writtens )
		{
			it->fadein( value );
		}
		
		if( globalYScale < globalYLine )
		{
			globalYScale += elapsedTime *5;
		}
		else
		{
			globalYScale = globalYLine;
		}
	}
	else
	{
		float value = elapsedTime *0xFF *2;
		escButton.fadeout( value );
		background.fadeout( value );
		username.fadeout( value );
		arrow.fadeout( value );
		for( auto &it :writtens )
		{
			it->fadeout( value );
		}
		
		if( globalYScale > 0 )
		{
			globalYScale -= elapsedTime *5;
		}
		else
		{
			globalYScale = 0;
		}
	}
	
	if( globalYScale != 0 && globalYScale != globalYLine )
	{
		background.setPosition( 0, screen_h -background.getHeight() +screen_h /288 );
		escButton.setPosition( background.getRight() -escButton.getWidth() -screen_w /192, background.getY() +screen_h /214 );
		
		escButton.setScale( 1, 1 *globalYScale /globalYLine );
		background.setScale( scale_x, scale_y *globalYScale /globalYLine );
		username.setScale( 1, 1 *globalYScale /globalYLine );
		
		for( auto &it :writtens )
		{
			it->setScale( 1, 1 *globalYScale /globalYLine );
		}
	}
}

void Chat::fadeout( float v, int min )
{
	escButton.fadeout( v, min );
	background.fadeout( v, min );
	username.fadeout( v, min );
	for( auto &it :writtens )
	{
		it->fadeout( v, min );
	}
}



bool& Chat::isOpen()
{
	return open;
}

bool Chat::isCommand()
{
	if( open && used )
	{
		used = false;
		return true;
	}
	
	return false;
}

bool Chat::findCommand( string line )
{
	if( writtenStrs[ 1 ] == line )
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
	setWritten();
}

void Chat::setWritten()
{
	float y0 = screen_h -screen_h /28;
	
	writtens[ 0 ]->setPosition( screen_w /256, y0 );
	if( writtenStrs[ 0 ].size() > 0 )
	{
		if( writtenStrs[ 0 ][ 0 ] == '@' )	writtens[ 0 ]->setColor( commandColor );
		else								writtens[ 0 ]->setColor( typicalColor );
	}
	
	for( unsigned i = 1; i < writtens.size(); i++ )
	{
		writtens[ i ]->setText( writtenStrs[ i ] );
		
		float y_adder = screen_h /26;
		for( unsigned j = 0; j < writtenStrs[ i ].size(); j++ )
		{
			if( static_cast <int> (writtenStrs[ i ][ j ]) == 10 )
			{
				y_adder += screen_h /26;
			}
		}
		
		writtens[ i ]->setPosition( username.getRight() +screen_w /256, writtens[ i -1 ]->getY() -y_adder );
		
		if( writtenStrs[ i ].size() > 0 )
		{
			if( writtenStrs[ i ][ 0 ] == '@' )	writtens[ i ]->setColor( commandColor );
			else								writtens[ i ]->setColor( typicalColor );
		}
	}
	
	writtens[ 0 ]->setText( writtenStrs[ 0 ] );
	
	if( writtens[ 0 ]->getRight() < background.getRight() )	writtens[ 0 ]->setPosition( screen_w /256, y0 );
	else	writtens[ 0 ]->setPosition( (background.getRight() -writtens[ 0 ]->getWidth()) -screen_w /256, y0 );
	
	if( writtenStrs[ 0 ].size() == 0 )	arrow.setPosition( 0, y0 );
	else	arrow.setPosition( writtens[ 0 ]->getRight(), y0 );
}

void Chat::setError()
{
	writtenStrs[ 1 ] = writtenStrs[ 1 ] +" - command doesn't exist";
	
	// Add \n if needed.
	string teststring = "";
	for( unsigned i = 0; i < writtenStrs[ 1 ].size(); i++ )
	{
		teststring += writtenStrs[ 1 ][ i ];
		writtens[ 0 ]->setText( teststring );
		
		if( writtens[ 0 ]->getWidth() +username.getWidth() +screen_w /64 >= background.getRight() )
		{
			string nextnewstring = "";
			for( unsigned j = 0; j < teststring.size() -1; j++ )
			{
				nextnewstring += teststring[ j ];
			}
			nextnewstring += "\n";
			nextnewstring += teststring[ teststring.size() -1 ];
			teststring = nextnewstring;
		}
	}
	
	writtenStrs[ 1 ] = teststring;
	
	setWritten();
}



void Chat::setCommandColor( sf::Color newColor )
{
	commandColor = newColor;
}

void Chat::setTypicalColor( sf::Color newColor )
{
	typicalColor = newColor;
}