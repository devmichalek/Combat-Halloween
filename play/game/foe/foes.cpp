#include "factory.h"
#include "own/file.h"
// #include "SFML/Graphics/RectangleShape.hpp"

Factory::Factory()
{
	myThread = NULL;
	free();
}

Factory::~Factory()
{
	free();
}

void Factory::free()
{
	type = -1;
	name = "";
	
	screen_w = 0;
	screen_h = 0;
	border_x = 0;
	border_y = 0;
	
	if( myThread != NULL )
	{
		delete myThread;
		myThread = NULL;
	}
	thread_ready = false;
	ready = 0;
	
	if( !foes.empty() )
	{
		for( auto &it :foes )
		{
			it->free();
			delete it;
			it = NULL;
		}
		
		foes.clear();
	}
	
	if( !lines.empty() )
	{
		lines.clear();
	}
	
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
}

void Factory::reset()
{
	border_x = 0;
	border_y = 0;
	
	if( myThread != NULL )
	{
		delete myThread;
		myThread = NULL;
	}
	thread_ready = false;
	ready = 0;
	
	if( !foes.empty() )
	{
		for( auto &it :foes )
		{
			it->free();
			delete it;
			it = NULL;
		}
		
		foes.clear();
	}
	
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
}

void Factory::load( float screen_w, float screen_h, int type, string name )
{
	free();
	
	this->type = type;
	this->name = name;
	this->screen_w = screen_w;
	this->screen_h = screen_h;
}

void Factory::draw( sf::RenderWindow* &window )
{
	float x;
	float y;
	sf::Uint8 t;
	
	for( unsigned i = 0; i < foes.size(); i++ )
	{
		t = foes[ i ]->getState();
		if( t < 0 )
		{
			continue;
		}
		
		x = foes[ i ]->getX();
		y = foes[ i ]->getY();
		
		if( x < border_x +screen_w && y < border_y +screen_h )
		{
			if( x +sprites[ t ]->getWidth() > border_x && y +sprites[ t ]->getHeight() > border_y )
			{
				
				
				sprites[ t ]->setOffset( foes[ i ]->getOffset() );
				sprites[ t ]->setPosition( x, y -sprites[ t ]->getHeight() );
				window->draw( sprites[ t ]->get() );
				
				// Just for test.
				/*
				sf::RectangleShape rectshape;
				rectshape.setSize( sf::Vector2f( 2, 50 ) );
				rectshape.setFillColor( sf::Color( 0xFF, 0xFF, 0xFF, 0xFF ) );
				
				rectshape.setPosition( sf::Vector2f( foes[ i ]->getLeft(), foes[ i ]->getY() ) );
				window->draw( rectshape );
				
				rectshape.setPosition( sf::Vector2f( foes[ i ]->getRight(), foes[ i ]->getY() ) );
				window->draw( rectshape );
				*/
			}
		}
	}
}

void Factory::fadein( float v, int max )
{
	for( auto &it :sprites )
	{
		it->fadein( v, max );
	}
}

void Factory::fadeout( float v, int min )
{
	for( auto &it :sprites )
	{
		it->fadeout( v, min );
	}
}

void Factory::mechanics( double elapsedTime )
{
	
}



bool Factory::isNull()
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

bool Factory::isReady()
{
	if( ready > 1 )
	{
		return true;
	}
	
	return false;
}

void Factory::setThread()
{
	if( !ready )
	{
		if( !thread_ready && myThread == NULL )
		{
			myThread = new std::thread( [=] { prepare(); } );
			myThread->detach();
		}
	}
}

void Factory::prepare()
{
	if( ready == 0 )	// load positions.
	{
		MyFile file;
		file.load( "txt/worlds/world_.txt" );
		if( file.is_good() )
		{
			// Line and bufor.
			string line = "";
			string bufor = "";
			unsigned start = 0;
			
			// Getline.
			getline( file.get(), line );
			
			
			// AUTHOR --------------------------------------------------------------------------
			for( unsigned i = start; i < line.size(); i++ )
			{
				if( line[ i ] == '|' )
				{
					start = i +1;
					// printf( "%s\n", bufor.c_str() );
					bufor = "";
					break;
				}
				
				bufor += line[ i ];
			}
			
			
			// MULTIPLIERS --------------------------------------------------------------------------
			float x_multiplier = 1;
			float y_multiplier = 1;
			
			// Set x_multiplier.
			for( unsigned i = start; i < line.size(); i++ )
			{
				if( line[ i ] == '|' )
				{
					start = i +1;
					x_multiplier = screen_w /con::stof( bufor );
					bufor = "";
					break;
				}
				
				bufor += line[ i ];
			}
			// printf( "%f\n", x_multiplier );
			
			// Set y_multiplier.
			for( unsigned i = start; i < line.size(); i++ )
			{
				if( line[ i ] == '|' )
				{
					start = i +1;
					y_multiplier = screen_h /con::stof( bufor );
					bufor = "";
					break;
				}
				
				bufor += line[ i ];
			}
			// printf( "%f\n", y_multiplier );
			
			
			// FS --------------------------------------------------------------------------
			vector <sf::Vector2f> fs_tiles;
			vector <sf::Uint8> types_tiles;
			for( unsigned i = start; i < line.size(); i++ )
			{
				if( line[ i ] == '|' )
				{
					bufor += ".";
					string nrstr = "";
					vector <string> data;
					
					for( unsigned j = 0; j < bufor.size(); j++ )
					{
						if( bufor[ j ] == '.' )
						{
							data.push_back( nrstr );
							nrstr = "";
						}
						else
						{
							nrstr += bufor[ j ];
						}
					}
					
					sf::Uint8 w = con::stoi( data[ 0 ] );
					sf::Uint8 t = con::stoi( data[ 1 ] );
					float x = con::stoi( data[ 2 ] ) *x_multiplier;
					float y = con::stoi( data[ 3 ] ) *y_multiplier;
					
					if( w == 4 )
					{
						if( t == type )
						{
							foes.push_back( new Skeleton );
							foes[ foes.size() -1 ]->setPosition( x, y );
							foes[ foes.size() -1 ]->setCenterX( x );
						}
					}
					else if( w == 0 )
					{
						fs_tiles.push_back( sf::Vector2f( x, y ) );
						types_tiles.push_back( t );
					}
					
					// Clear.
					bufor = "";
				}
				else
				{
					bufor += line[ i ];
				}
			}
			
			positioning( fs_tiles, types_tiles );
			
			// Inform that everything is ok.
			ready = 1;
		}
		file.free();
	}
	
	if( ready == 1 )
	{
		// prepare message
		string message = "name=" +name;
		
		// prepare the request
		sf::Http::Request request( "/combathalloween/getline.php", sf::Http::Request::Post );
		
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
				string line = "";
				for( unsigned i = 0; i < echostring.size(); i++ )
				{
					if( echostring[ i ] == ',' )
					{
						lines.push_back( con::stoi( line ) );
						line = "";
					}
					
					line += echostring[ i ];
				}
				lines.push_back( con::stoi( line ) );
				
				// Load sprites.
				for( unsigned i = 0; i < lines.size(); i++ )
				{
					sprites.push_back( new MySprite() );
					sprites[ i ]->setIdentity( "foes-skeletonsprites" );
					sprites[ i ]->load( "images/play/foes/" +name +"/" +con::itos(i) +".png", lines[ i ] );
					sprites[ i ]->setScale( screen_w /2560, screen_h /1440 );
				}
				
				ready = 2;
			}
		}
		
		
	}
	
	// Inform that thread is ready for next action.
	thread_ready = true;
}

void Factory::positioning( vector <sf::Vector2f> fs, vector <sf::Uint8> types )
{
	// Setting left and right of particular foe...
	MySprite block;
	block.setIdentity( "foes-block" );
	block.load( "images/play/tiles/0.png" );
	block.setScale( screen_w /2560, screen_h /1440 );

	float foe_x = 0;
	float foe_y = 0;
	float block_x = 0;
	float block_y = 0;
	int success = -1;
	
	for( int i = 0; i < static_cast <int> (foes.size()); i++ )
	{
		foe_x = foes[ i ]->getX();
		foe_y = foes[ i ]->getY() +sprites[ 1 ]->getHeight();
		success = -1;
		
		for( unsigned j = 0; j < fs.size(); j++ )
		{
			if( types[ j ] >= 0 && types[ j ] <= 8 )
			{
				block_x = fs[ j ].x;
				block_y = fs[ j ].y;
				
				if( foe_x > block_x && foe_x < block_x +block.getWidth() )
				{
					if( foe_y > block_y && foe_y < block_y +block.getHeight() )
					{
						// printf( "fx:%f fy:%f  bx:%f by:%f bw:%f\n", foe_x, foe_y, block_x, block_y, block.getWidth() );
						success = j;
						break;
					}
				}
			}
		}
		
		if( success < 0 )	// Wrong put foe.
		{
			foes.erase( foes.begin() +i );
			i --;
		}
		else
		{
			
			float good_left = block_x;
			float good_right = block_x +block.getWidth();
			
			// Building path for foe, start with left.
			for( int k = success -1; k >= 0; k-- )
			{
				if( fs[ k ].y == block_y )
				{
					if( types[ k ] >= 0 && types[ k ] <= 8 )
					{
						if( fs[ k ].x == good_left -block.getWidth() )
						{
							good_left -= block.getWidth();
						}
					}
				}
			}
			
			// right
			for( unsigned k = success +1; k < fs.size(); k++ )
			{
				if( fs[ k ].y == block_y )
				{
					if( types[ k ] >= 0 && types[ k ] <= 8 )
					{
						if( fs[ k ].x == good_right )
						{
							good_right += block.getWidth();
						}
					}
				}
			}
			
			// printf( "%f %f\n", good_left, good_right );
			foes[ i ]->setLeft( good_left );
			foes[ i ]->setRight( good_right );
			foes[ i ]->setPosition( good_left +((good_right -good_left)/2), block_y );
			
			// delete if surface is too small
			if( good_right -good_left <= block.getWidth() )
			{
				foes.erase( foes.begin() +i );
				i --;
			}
		}
	}

	block.free();
}



void Factory::setBorderX( float x )
{
	border_x = x;
}

void Factory::setBorderY( float y )
{
	border_y = y;
}



bool Factory::isHarmed( sf::Rect <float> rect )
{
	float x;
	float y;
	sf::Uint8 t;
	
	for( unsigned i = 0; i < foes.size(); i++ )
	{
		if( !foes[ i ]->isAttack() )
		{
			continue;
		}
		
		x = foes[ i ]->getX();
		y = foes[ i ]->getY();
		t = foes[ i ]->getState();
		
		if( x < border_x +screen_w && y < border_y +screen_h )
		{
			if( x +sprites[ t ]->getWidth() > border_x && y +sprites[ t ]->getHeight() > border_y )
			{
				sprites[ t ]->setPosition( x, y );
				if( sprites[ t ]->checkCollisionRect( rect ) )
				{
					return true;
				}
			}
		}
	}
	
	return false;
}

void Factory::walk( sf::Rect <float> rect )
{
	float l;
	float r;
	float y;
	
	for( unsigned i = 0; i < foes.size(); i++ )
	{
		if( !foes[ i ]->isAlive() )
		{
			l = foes[ i ]->getLeft();
			r = foes[ i ]->getRight();
			y = foes[ i ]->getY();
			
			if( rect.left +rect.width > l && rect.left < r )
			{
				if( rect.top +rect.height/2 < y && rect.top +rect.height > y -rect.height/2 )
				{
					if( !foes[ i ]->wasAppear() )
					{
						foes[ i ]->setAppear();
					}
					else if( foes[ i ]->isIdle() || foes[ i ]->isWalk() )
					{
						
					}
				}
			}
		}
	}
}