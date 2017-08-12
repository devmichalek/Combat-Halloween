#include "worldtable.h"
#include "own/file.h"
#include <SFML/Network.hpp>

Star::Star()
{
	free();
}

Star::~Star()
{
	free();
}

void Star::free()
{
	silver = 0;
	gold = 0;
	coin_medal = false;
	star_medal = false;
	x_medal = false;
}




Worldtable::Worldtable()
{
	myThread = NULL;
	free();
}

Worldtable::~Worldtable()
{
	free();
}

void Worldtable::free()
{
	screen_w = 0;
	screen_h = 0;
	username = "";
	
	ready = 0;
	chosen = -1;
	button.free();
	
	if( !locks.empty() )
	{
		locks.clear();
	}
	
	if( !xs.empty() )
	{
		xs.clear();
	}
	
	if( !ys.empty() )
	{
		ys.clear();
	}
	
	if( !texts.empty() )
	{
		for( auto &it :texts )
		{
			it->free();
			delete it;
			it = NULL;
		}
		
		texts.clear();
	}
	
	if( myThread != NULL )
	{
		delete myThread;
		myThread = NULL;
	}
	thread_ready = false;
	
	reloadButton.free();
	information.free();
	
	gold_star.free();
	silver_star.free();
	coin_medal.free();
	star_medal.free();
	x_medal.free();
	
	if( !stars.empty() )
	{
		for( auto &it :stars )
		{
			it->free();
			delete it;
			it = NULL;
		}
		
		stars.clear();
	}
	
	left.free();
	right.free();
	
	click.free();
}



void Worldtable::load( float screen_w, float screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	button.setIdentity( "worldtable-button" );
	button.load( "images/level/level.png", 3 );
	button.setScale( screen_w /2560, screen_h /1440 );
	
	reloadButton.setIdentity( "worldtable-reloadButton" );
	reloadButton.load( "images/menu/reload.png", 3 );
	reloadButton.setScale( screen_w /2560, screen_h /1440 );
	
	information.setIdentity( "worldtable-information" );
	information.setFont( "fonts/jcandlestickextracond.ttf" );
	
	
	
	gold_star.setIdentity( "worldtable-gold_star" );
	gold_star.load( "images/level/gold_star.png" );
	gold_star.setScale( screen_w /2560, screen_h /1440 );
	
	silver_star.setIdentity( "worldtable-silver_star" );
	silver_star.load( "images/level/silver_star.png" );
	silver_star.setScale( screen_w /2560, screen_h /1440 );
	
	coin_medal.setIdentity( "worldtable-coin_medal" );
	coin_medal.load( "images/level/c_medal.png" );
	coin_medal.setScale( screen_w /2560, screen_h /1440 );
	
	star_medal.setIdentity( "worldtable-star_medal" );
	star_medal.load( "images/level/s_medal.png" );
	star_medal.setScale( screen_w /2560, screen_h /1440 );
	
	x_medal.setIdentity( "worldtable-x_medal" );
	x_medal.load( "images/level/x_medal.png" );
	x_medal.setScale( screen_w /2560, screen_h /1440 );
	
	
	
	left.setIdentity( "worldtable-left" );
	left.load( "images/level/left.png", 3 );
	left.setScale( screen_w /2560, screen_h /1440 );
	left.setPosition( screen_w/256, screen_h/2 -left.getHeight()/2 );
	
	right.setIdentity( "worldtable-right" );
	right.load( "images/level/right.png", 3 );
	right.setScale( screen_w /2560, screen_h /1440 );
	right.setPosition( screen_w -right.getWidth() -screen_w/256, screen_h/2 -right.getHeight()/2 );
	
	click.setIdentity( "worldtable-click" );
	click.load( "sounds/click.wav" );
}

void Worldtable::handle( sf::Event& event )
{
	if( event.type == sf::Event::MouseButtonPressed )
	{
		if( event.mouseButton.button == sf::Mouse::Left )
		{
			float x = event.mouseButton.x;
			float y = event.mouseButton.y;
			
			if( ready < 2 ) // we can click reload button
			{
				if( reloadButton.checkCollisionCircle( x, y ) )
				{
					click.play();
					reloadButton.setOffset( 1 );
					setThread();
				}
			}
			else
			{
				bool immunity = false;
				// chosing world
				if( !xs.empty() )
				{
					for( unsigned i = 0; i < xs.size(); i++ )
					{
						if( !locks[ i ] )
						{
							if( xs[ i ] > 0 && xs[ i ] < screen_w )
							{
								button.setPosition( xs[ i ], ys[ i ] );
								if( button.checkCollisionCircle( x, y ) )
								{
									chosen = i;
									immunity = true;
									break;
								}
							}
						}
					}
				}
				
				// left
				bool success = false;
				for( auto &it :xs )
				{
					if( it < 0 )
					{
						success = true;
						break;
					}
				}
				if( success )
				{
					if( left.checkCollisionCircle( x, y ) )
					{
						click.play();
						left.setOffset( 1 );
						immunity = true;
						
						for( unsigned i = 0; i < xs.size(); i++ )
						{
							xs[ i ] += screen_w;
							texts[ i ]->move( screen_w, 0 );
						}
					}
				}
				
				// right
				success = false;
				for( auto &it :xs )
				{
					if( it > screen_w )
					{
						success = true;
						break;
					}
				}
				if( success )
				{
					if( right.checkCollisionCircle( x, y ) )
					{
						click.play();
						right.setOffset( 1 );
						immunity = true;
						
						for( unsigned i = 0; i < xs.size(); i++ )
						{
							xs[ i ] -= screen_w;
							texts[ i ]->move( -screen_w, 0 );
						}
					}
				}
				
				if( !immunity )
				{
					chosen = -1;
				}
			}
		}
	}
	
	else if( event.type == sf::Event::MouseButtonReleased )
	{
		reloadButton.setOffset( 0 );
		left.setOffset( 0 );
		right.setOffset( 0 );
	}
}

void Worldtable::draw( sf::RenderWindow* &window )
{
	if( ready < 2 )
	{
		window->draw( reloadButton.get() );
		window->draw( information.get() );
	}
	else
	{
		// left
		bool success = false;
		for( auto &it :xs )
		{
			if( it < 0 )
			{
				success = true;
				break;
			}
		}
		if( success )
		{
			window->draw( left.get() );
		}
		
		// right
		success = false;
		for( auto &it :xs )
		{
			if( it > screen_w )
			{
				success = true;
				break;
			}
		}
		if( success )
		{
			window->draw( right.get() );
		}
		
		
		if( !xs.empty() && !ys.empty() )
		{
			for( unsigned i = 0; i < xs.size(); i++ )
			{
				if( xs[ i ] > 0 && xs[ i ] < screen_w )
				{
					button.setPosition( xs[ i ], ys[ i ] );
					
					if( locks[ i ] )
					{
						button.setOffset( 2 );
					}
					else if( chosen != -1 && static_cast <int> (i) == chosen )
					{
						button.setOffset( 1 );
					}
					else
					{
						button.setOffset( 0 );
					}
					
					window->draw( button.get() );
				}
			}
		}
		
		// Draw reward.
		if( !stars.empty() )
		{
			for( unsigned i = 0; i < stars.size(); i++ )
			{
				if( xs[ i ] < 0 || xs[ i ] > screen_w )
				{
					continue;
				}
				
				if( stars[ i ]->gold > 0 )
				{
					for( int j = 0; j < stars[ i ]->gold; j++ )
					{
						gold_star.setPosition( xs[ i ] +gold_star.getWidth()/3 *j, ys[ i ] -gold_star.getHeight() );
						window->draw( gold_star.get() );
					}
				}
				else if( stars[ i ]->silver > 0 )
				{
					for( int j = 0; j < stars[ i ]->silver; j++ )
					{
						silver_star.setPosition( xs[ i ] +silver_star.getWidth()/3 *j, ys[ i ] -silver_star.getHeight() );
						window->draw( silver_star.get() );
					}
				}
				
				if( stars[ i ]->coin_medal )
				{
					coin_medal.setPosition( xs[ i ] +gold_star.getWidth()*4/3, ys[ i ] -coin_medal.getHeight() );
					window->draw( coin_medal.get() );
				}
				
				if( stars[ i ]->star_medal )
				{
					star_medal.setPosition( xs[ i ] +gold_star.getWidth()*5/3, ys[ i ] -star_medal.getHeight() );
					window->draw( star_medal.get() );
				}
				
				if( stars[ i ]->x_medal )
				{
					x_medal.setPosition( xs[ i ] +gold_star.getWidth()*2, ys[ i ] -x_medal.getHeight() );
					window->draw( x_medal.get() );
				}
			}
		}
		
		for( unsigned i = 0; i < texts.size(); i++ )
		{
			if( !locks[ i ] )
			{
				window->draw( texts[ i ]->get() );
			}
		}
	}
	
	// Delete thread if is ready
	if( thread_ready )
	{
		delete myThread;
		myThread = NULL;
		thread_ready = false;
	}
}



void Worldtable::fadein( float v, int max )
{
	reloadButton.fadein( v, max );
	information.fadein( v, max );
	
	if( ready == 2 )
	{
		button.fadein( v, max );
		for( auto &it: texts )
		{
			it->fadein( v, max );
		}
		
		gold_star.fadein( v, max );
		silver_star.fadein( v, max );
		coin_medal.fadein( v, max );
		star_medal.fadein( v, max );
		x_medal.fadein( v, max );
		
		left.fadein( v, max );
		right.fadein( v, max );
	}
}

void Worldtable::fadeout( float v, int min )
{
	reloadButton.fadeout( v, min );
	information.fadeout( v, min );
	
	if( ready == 2 )
	{
		button.fadeout( v, min );
		for( auto &it: texts )
		{
			it->fadeout( v, min );
		}
		
		gold_star.fadeout( v, min );
		silver_star.fadeout( v, min );
		coin_medal.fadeout( v, min );
		star_medal.fadeout( v, min );
		x_medal.fadeout( v, min );
		
		left.fadeout( v, min );
		right.fadeout( v, min );
	}
}



int Worldtable::isChosen()
{
	if( chosen != -1 )
	{
		return true;
	}
	
	return false;
}



void Worldtable::setThread()
{
	if( ready < 2 )
	{
		if( !thread_ready )
		{
			// Setting loading text.
			information.setText( "loading..." );
			information.setSize( screen_h /28 );
			information.setPosition( screen_w/2 -information.getWidth()/2 -reloadButton.getWidth()/2 -screen_w/256, screen_h /2.2 );
			reloadButton.setPosition( information.getRight() +screen_w/256, information.getY() -reloadButton.getHeight() /3 );
			
			myThread = new std::thread( Worldtable::setValues, this );
			myThread->detach();
		}
	}
}

void Worldtable::setValues()
{
	bool success = true;
	
	if( ready == 0 )
	{
		// prepare the request
		sf::Http::Request request( "/combathalloween/nrworlds.php", sf::Http::Request::Post );
		
		request.setBody( "" );
		
		// send the request
		sf::Http http( "http://adrianmichalek.pl/" );
		sf::Http::Response response = http.sendRequest( request );
		
		// check the status
		if( response.getStatus() != sf::Http::Response::Ok )
		{
			success = false;
		}
		else
		{
			string echostring = response.getBody();
			
			if( echostring == "0" )	// error
			{
				success = false;
			}
			else
			{
				int amount = con::stoi( echostring );
				int amount_buf = amount +1;
				int margin_w = 7;
				int margin_h = 6;
				int rows = static_cast <int> (screen_h /button.getHeight()) -margin_h;
				int columns = static_cast <int> (screen_w /button.getWidth()) -margin_w;
				
				float border_w = screen_w /64;
				float border_h = screen_h /18;
				float start_x = screen_w/2 -( button.getWidth()*columns +(border_w*(columns-1)) )/2;
				float start_y = screen_h/2 -( button.getHeight()*rows +(border_h*(rows-1)) )/2;
				
				float add = 0;
				while( amount )
				{
					for( int i = 0; i < rows; i++ )
					{
						for( int j = 0; j < columns; j++ )
						{
							texts.push_back( new MyText );
							texts[ texts.size() -1 ]->setIdentity( "worldtable-texts" );
							texts[ texts.size() -1 ]->setFontByFont( information.getFont() );
							texts[ texts.size() -1 ]->setText( con::itos(amount_buf -amount) );
							texts[ texts.size() -1 ]->setSize( screen_h /28 );
							texts[ texts.size() -1 ]->setColor( sf::Color( 0xDD, 0xDD, 0xDD ) );
							float newX = start_x +button.getWidth()/2 -texts[ texts.size() -1 ]->getWidth()/2;
							float newY = start_y +button.getHeight()/2 -texts[ texts.size() -1 ]->getHeight();
							texts[ texts.size() -1 ]->setPosition( newX, newY );
							
							xs.push_back( start_x );
							ys.push_back( start_y );
							start_x += border_w +button.getWidth();
							
							locks.push_back( true );
							
							amount --;
							if( amount == 0 )
							{
								break;
							}
						}
						
						start_x = screen_w/2 -( button.getWidth()*columns +(border_w*(columns-1)) )/2 +add;
						start_y += border_h +button.getHeight();
						
						if( amount == 0 )
						{
							break;
						}
					}
					
					start_y = screen_h/2 -( button.getHeight()*rows +(border_h*(rows-1)) )/2;
					add += screen_w;
					start_x = screen_w/2 -( button.getWidth()*columns +(border_w*(columns-1)) )/2 +add;
				}
				
				ready = 1;
			}
		}
	}
	
	if( ready == 1 )
	{
		// prepare message
		username = "adriqun";
		string message = "username=" +username;
		
		// prepare the request
		sf::Http::Request request( "/combathalloween/cup.php", sf::Http::Request::Post );
		
		request.setBody( message );
		
		// send the request
		sf::Http http( "http://adrianmichalek.pl/" );
		sf::Http::Response response = http.sendRequest( request );
		
		// check the status
		if( response.getStatus() != sf::Http::Response::Ok )
		{
			success = false;
		}
		else
		{
			string echostring = response.getBody();
			
			if( echostring == "0" )	// error
			{
				success = false;
			}
			else
			{
				string line = "";
				for( unsigned i = 0; i < echostring.size() -1; i++ )
				{
					// nr world
					if( echostring[ i ] == '&' )
					{
						line = "";
						for( unsigned j = i +1; j < echostring.size(); j++ )
						{
							if( echostring[ j ] == '*' )
							{
								i = j;
								break;
							}
							
							line += echostring[ j ];
						}
						
						locks[ con::stoi( line ) -1 ] = false;
					}
					
					// reward, cups, medals etc.
					if( echostring[ i ] == '*' )
					{
						line = "";
						for( unsigned j = i +1; j < echostring.size(); j++ )
						{
							if( echostring[ j ] == '&' )
							{
								i = j -1;
								break;
							}
							
							line += echostring[ j ];
						}
						
						stars.push_back( new Star );
						for( unsigned j = 0; j < line.size(); j++ )
						{
							// medals
							if( line[ j ] == 'c' )	stars[ stars.size() -1 ]->coin_medal = true;
							if( line[ j ] == 'p' )	stars[ stars.size() -1 ]->star_medal = true;
							if( line[ j ] == 'x' )	stars[ stars.size() -1 ]->x_medal = true;
							
							// stars
							if( line[ j ] == 'g' ) // gold
							{
								stars[ stars.size() -1 ]->gold = static_cast <int> (line[ j +1 ]) -48;
							}
							else if( line[ j ] == 's' ) // silver
							{
								stars[ stars.size() -1 ]->silver = static_cast <int> (line[ j +1 ]) -48;
							}
						}
					}
				}
				
				// printf( "%s\n", echostring.c_str() );
				ready = 2;
			}
		}
	}
	
	// error
	if( !success )
	{
		information.setText( "error" );
		information.setColor( sf::Color( 0xF2, 0x58, 0x3E ) );
		information.setSize( screen_h /28 );
		information.setPosition( screen_w/2 -information.getWidth()/2 -reloadButton.getWidth()/2 -screen_w/256, screen_h /2.2 );
		reloadButton.setPosition( information.getRight() +screen_w/256, information.getY() -reloadButton.getHeight() /3 );
	}
	
	thread_ready = true;
}

void Worldtable::reload()
{
	ready = 0;
	chosen = -1;
	
	if( !locks.empty() )
	{
		locks.clear();
	}
	
	if( !xs.empty() )
	{
		xs.clear();
	}
	
	if( !ys.empty() )
	{
		ys.clear();
	}
	
	if( !texts.empty() )
	{
		for( auto &it :texts )
		{
			it->free();
			delete it;
			it = NULL;
		}
		
		texts.clear();
	}
	
	if( myThread != NULL )
	{
		delete myThread;
		myThread = NULL;
	}
	thread_ready = false;
	
	if( !stars.empty() )
	{
		for( auto &it :stars )
		{
			it->free();
			delete it;
			it = NULL;
		}
		
		stars.clear();
	}
	
	information.setFont( "fonts/jcandlestickextracond.ttf" );
}

void Worldtable::setUsername( string line )
{
	username = line;
}



void Worldtable::setPlayable( bool playable )
{
	click.setPlayable( playable );
}

void Worldtable::setVolume( float volume )
{
	click.setVolume( volume );
}
