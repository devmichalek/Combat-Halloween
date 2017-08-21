#include "knight.h"
#include "own/file.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Network.hpp>

Knight::Knight()
{
	myThread = NULL;
	free();
}

Knight::~Knight()
{
	free();
}

void Knight::free()
{
	if( !keys.empty() )
	{
		keys.clear();
	}
	
	line = 0;
	which = IDLE;
	offset = 0;
	if( !sprites.empty() )
	{
		for( auto &it :sprites )
		{
			it->free();
			delete it;
			it = NULL;
		}
		
		sprites.clear();
	}
	
	if( !x1s.empty() )
	{
		x1s.clear();
	}
	
	if( !x2s.empty() )
	{
		x2s.clear();
	}
	
	right = true;
	flip = 0;
	
	username = "adriqun";
	armour = 0;
	damage = 0;
	velocity = 0;
	heartpoints = 0;
	
	
	running = 0;
	running_line = 0;
	
	jumping = 0;
	jumping_line = 0;
	
	
	if( myThread != NULL )
	{
		delete myThread;
		myThread = NULL;
	}
	thread_ready = false;
	ready = false;
}



void Knight::load( float screen_w, float screen_h )
{
	free();
	
	// Set keys.
	MyFile file;
	file.load( "txt/keys_current.txt" );
	if( file.is_good() )
	{
		string line;
		for( unsigned i = 0; i < AMOUNT_K; i++ )
		{
			getline( file.get(), line );
			keys.push_back( con::stoi( line ) );
		}
	}
	file.free();
	
	line = 10;
	for( unsigned i = 0; i < AMOUNT; i++ )
	{
		sprites.push_back( new MySprite() );
		sprites[ i ]->setIdentity( "knight-sprites" );
		sprites[ i ]->load( "images/play/knight/" +con::itos( i ) +".png", line );
		sprites[ i ]->setScale( screen_w /2560, screen_h /1440 );
		
		x1s.push_back( screen_w /128 );
		x2s.push_back( screen_w /128 +sprites[ i ]->getWidth() );
		sprites[ i ]->setPosition( x1s[ i ], screen_h -sprites[ IDLE ]->getHeight() *2 );
	}
	
	
	moveX( 0 );
	
	// Features.
	armour = 85;
	damage = 10;
	velocity = 100;
	heartpoints = 90;
	
	// Activity variables.
	running_line = 0.5;
	jumping_line = 4;
}

void Knight::draw( sf::RenderWindow* &window )
{
	sprites[ which ]->setOffset( offset );
	window->draw( sprites[ which ]->get() );
}

void Knight::mechanics( double elapsedTime )
{
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( keys[ JUMP_K ] ) ) && jumping < jumping_line )
	{
		if( jumping == 0 )
		{
			offset = 0;
		}
		
		if( offset < line -1 && offset > line /2 )
		{
			which = JUMP;
			offset = 0;
			jumping ++;
		}
	}
	
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( keys[ LEFT_K ] ) ) )
	{
		right = false;
		if( which != JUMP )
		{
			if( running > running_line )
			{
				which = RUN;
			}
			else
			{
				which = WALK;
			}
		}
		
		int multiplier = 1;
		if( running > running_line )	multiplier ++;
		if( which == JUMP )				multiplier ++;
		
		if( flip != 1 )
		{
			flip = 3;
		}
		if( running < running_line *1.5 )
		{
			running += elapsedTime;
		}
			
		
		moveX( -elapsedTime *velocity *multiplier );
	}
	else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( keys[ RIGHT_K ] ) ) )
	{
		right = true;
		if( which != JUMP )
		{
			if( running > running_line )
			{
				which = RUN;
			}
			else
			{
				which = WALK;
			}
		}
		
		int multiplier = 1;
		if( running > running_line )	multiplier ++;
		if( which == JUMP )				multiplier ++;
		
		if( flip != 0 )
		{
			flip = 2;
		}
		
		if( running < running_line *1.5 )
		{
			running += elapsedTime;
		}
		
		moveX( elapsedTime *velocity *multiplier );
	}
	else
	{
		if( which != JUMP )
		{
			which = IDLE;
		}
		
		
		if( running > -running_line/2 )
		{
			running -= elapsedTime;
		}
		
		if( jumping < jumping_line )
		{
			jumping += elapsedTime;
		}
	}
	
	
	
	// Animation.
	offset += elapsedTime *25;
	if( offset >= line )
	{
		offset = 0;
		
		if( which == JUMP )
		{
			which = IDLE;
		}
		
		if( jumping > 0 )
		{
			jumping -= 0.75;
		}
	}
	
	// If flip.
	flipSprites();
}


void Knight::fadein( float v, int max )
{
	for( auto &it :sprites )
	{
		it->fadein( v, max );
	}
}

void Knight::fadeout( float v, int min )
{
	for( auto &it :sprites )
	{
		it->fadeout( v, min );
	}
}



void Knight::setMoving( sf::Uint8 moving )
{
	this->moving = moving;
}

void Knight::moveX( float x )
{
	for( auto &it :x1s )
	{
		it += x;
	}
	
	for( auto &it :x2s )
	{
		it += x;
	}
	
	if( right )
	{
		for( unsigned i = 0; i < sprites.size(); i++ )
		{
			sprites[ i ]->setPosition( x1s[ i ], sprites[ i ]->getY() );
		}
	}
	else
	{
		for( unsigned i = 0; i < sprites.size(); i++ )
		{
			sprites[ i ]->setPosition( x2s[ i ], sprites[ i ]->getY() );
		}
	}
}

void Knight::flipSprites()
{
	if( flip == 2 )
	{
		for( auto &it :sprites )
		{
			it->flipHorizontally();
		}
		
		flip = 0;
	}
	else if( flip == 3 )
	{
		for( auto &it :sprites )
		{
			it->flipHorizontally();
		}
		
		flip = 1;
	}
}



bool Knight::isReady()
{
	return ready;
}

bool Knight::isNull()
{
	// Delete thread.
	if( myThread != NULL && thread_ready )
	{
		delete myThread;
		myThread = NULL;
		thread_ready = false;
	}
	
	if( myThread == NULL )
	{
		return true;
	}
	
	return false;
}

void Knight::setThread()
{
	if( !ready )
	{
		if( !thread_ready && myThread == NULL )
		{
			myThread = new std::thread( [=] { setFeatures(); } );
			myThread->detach();
		}
	}
}

void Knight::setFeatures()
{
	// prepare message
	string message = "username=" +username;
	
	// prepare the request
	sf::Http::Request request( "/combathalloween/getparts.php", sf::Http::Request::Post );
	
	// encode the parameters in the request body
	request.setBody( message );
	
	// send the request
	sf::Http http( "http://adrianmichalek.pl/" );
	sf::Http::Response response = http.sendRequest( request );
	
	// check the status
	if( response.getStatus() == sf::Http::Response::Ok )
	{
		string echostring = response.getBody();
		
		if( echostring != "0" )	// success
		{
			float armour_temporary = 0;
			float damage_temporary = 0;
			float velocity_temporary = 0;
			float heartpoints_temporary = 0;
			
			for( unsigned i = 0; i < echostring.size(); i++ )
			{
				if( echostring[ i ] == 'c' )
				{
					for( unsigned j = i +1; j < echostring.size(); j++ )
					{
						if( echostring[ j ] == 'a' )
						{
							i = j -1;
							break;
						}
					}
				}
				
				else if( echostring[ i ] == 'a' || echostring[ i ] == 'h' || 
						 echostring[ i ] == 'd' || echostring[ i ] == 's' )
				{
					int was = i;
					string value = "";
					for( unsigned j = i +1; j < echostring.size(); j++ )
					{
						if( isalpha( echostring[ j ] ) )
						{
							i = j -1;
							break;
						}
						else
						{
							value += echostring[ j ];
						}
					}
					
					// printf( "%f\n", con::stof( value ) );
					switch( echostring[ was ] )
					{
						case 'a': armour_temporary += 		con::stof( value );	break;
						case 'h': heartpoints_temporary += 	con::stof( value );	break;
						case 'd': damage_temporary += 		con::stof( value );	break;
						case 's': velocity_temporary +=		con::stof( value );	break;
					}
				}
			}
			
			ready = true;
			armour = armour +(armour*armour_temporary /100);
			damage = damage +(damage*damage_temporary /100);
			velocity = velocity +(velocity*velocity_temporary /100);
			heartpoints = heartpoints +(heartpoints*heartpoints_temporary /100);
			printf( "a: %f  h: %f  d: %f  s: %f\n", armour, heartpoints, damage, velocity );
		}
	}
	
	thread_ready = true;
}



void Knight::setUsername( string line )
{
	this->username = line;
}



float Knight::getX()
{
	return 0;
}

float Knight::getY()
{
	return 0;
}
