#include "factory.h"
#include "own/file.h"
#include <SFML/Network.hpp>
#include "play/game/foe/skeleton.h"

template <typename F>
Factory <F>::Factory()
{
	myThread = NULL;
	free();
}

template <typename F>
Factory <F>::~Factory()
{
	free();
}

template <typename F>
void Factory <F>::free()
{
	bar.free();
	table.free();
	
	balloonchat.free();
	
	type = -1;
	name = "";
	collision = false;
	
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
	ready = false;
	
	damaged = -1;
	
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

template <typename F>
void Factory <F>::reset()
{
	border_x = 0;
	border_y = 0;
	collision = false;
	
	if( myThread != NULL )
	{
		delete myThread;
		myThread = NULL;
	}
	thread_ready = false;
	ready = false;
	
	damaged = -1;
	
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

template <typename F>
void Factory <F>::load( float screen_w, float screen_h, int type, string name )
{
	free();
	
	bar.setIdentity( "factory-foebar" );
	bar.load( "images/play/foes/foebar.png" );
	bar.setScale( screen_w /2560, screen_h /1440 );
	
	table.setIdentity( "factory-foetable" );
	table.load( "images/play/foes/foetable.png" );
	table.setScale( screen_w /2560, screen_h /1440 );
	
	balloonchat.load( screen_w, screen_h );
	
	rectcollisionwalk.setFillColor( sf::Color( 0xFF, 0x40, 0xFF, 0xAA ) );
	rectcollisionattack.setFillColor( sf::Color( 0xCC, 0, 0, 0xAA ) );
	
	this->type = type;
	this->name = name;
	this->screen_w = screen_w;
	this->screen_h = screen_h;
}

template <typename F>
void Factory <F>::draw( sf::RenderWindow* &window )
{
	float x;
	float y;
	int t;
	
	for( unsigned i = 0; i < foes.size(); i++ )
	{
		t = foes[ i ]->getState();
		if( t < 0 )
		{
			continue;
		}
		
		x = foes[ i ]->getX();
		y = foes[ i ]->getY();
		sprites[ t ]->setScale( foes[ i ]->getXScale(), foes[ i ]->getYScale() );
		
		if( x < border_x +screen_w && y -sprites[ t ]->getHeight() < border_y +screen_h )
		{
			if( x +sprites[ t ]->getWidth() > border_x && y +sprites[ t ]->getHeight() > border_y )
			{
				sprites[ t ]->setOffset( foes[ i ]->getOffset() );
				sprites[ t ]->setPosition( x, y -sprites[ t ]->getHeight() );
				window->draw( sprites[ t ]->get() );
				
				// Just for test.
				if( collision )
				{
					rectcollisionwalk.setSize( sf::Vector2f( foes[ i ]->getRealWidth(), foes[ i ]->getRealHeight() ) );
					rectcollisionwalk.setPosition( sf::Vector2f( foes[ i ]->getRealX(), foes[ i ]->getRealY() ) );
					window->draw( rectcollisionwalk );
					
					if( foes[ i ]->isAttacking( true ) )
					{
						rectcollisionattack.setSize( sf::Vector2f( foes[ i ]->getAttackWidth(), foes[ i ]->getAttackHeight() ) );
						rectcollisionattack.setPosition( sf::Vector2f( foes[ i ]->getAttackX(), foes[ i ]->getAttackY() ) );
						window->draw( rectcollisionattack );
					}
				}
				
				// Comments from foes.
				if( foes[ i ]->showText() )
				{
					balloonchat.setText( foes[ i ]->getText() );
					balloonchat.setPosition( foes[ i ]->getRealX(), foes[ i ]->getRealY() );
					balloonchat.draw( window );
				}
				
				// Info.
				table.setPosition( foes[ i ]->getRealX() +foes[ i ]->getRealWidth()/2 -table.getWidth()/2, y -sprites[ t ]->getHeight() -table.getHeight() *1.5 );
				window->draw( table.get() );
				
				bar.setColor( sf::Color( 0xFF -(foes[ i ]->getArmour()/5), 0, 0 ) );
				bar.setScale( foes[ i ]->getHPScale() *screen_w /2560, screen_h /1440 );
				bar.setPosition( table.getX(), table.getY() );
				window->draw( bar.get() );
			}
		}
	}
}

template <typename F>
void Factory <F>::fadein( float v, int max )
{
	bar.fadein( v, max );
	table.fadein( v, max );
	balloonchat.fadein( v, max );
	
	for( auto &it :sprites )
	{
		it->fadein( v, max );
	}
}

template <typename F>
void Factory <F>::fadeout( float v, int min )
{
	bar.fadeout( v, min );
	table.fadeout( v, min );
	balloonchat.fadeout( v, min );
	
	for( auto &it :sprites )
	{
		it->fadeout( v, min );
	}
}

template <typename F>
void Factory <F>::mechanics( double elapsedTime )
{
	float x;
	float y;
	int t;
	
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
			sprites[ t ]->setScale( foes[ i ]->getXScale(), foes[ i ]->getYScale() );
			if( x +sprites[ t ]->getWidth() > border_x && y +sprites[ t ]->getHeight() > border_y )
			{
				foes[ i ]->mechanics( elapsedTime );
			}
		}
	}
}



template <typename F>
void Factory <F>::turnCollision( bool collision )
{
	this->collision = collision;
}

template <typename F>
bool Factory <F>::getCollision()
{
	return collision;
}




template <typename F>
bool Factory <F>::isNull()
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

template <typename F>
bool Factory <F>::isReady()
{
	return ready;
}

template <typename F>
void Factory <F>::setThread()
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

template <typename F>
void Factory <F>::prepare()
{
	bool success = false;
	vector <sf::Vector2f> fs_tiles;
	vector <sf::Uint8> types_tiles;
	
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
		float this_screen_h = 0;
		
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
				this_screen_h = con::stof( bufor );
				y_multiplier = screen_h /con::stof( bufor );
				bufor = "";
				break;
			}
			
			bufor += line[ i ];
		}
		// printf( "%f\n", y_multiplier );
		
		// The margin of error.
		x_multiplier -= 0.03;
		y_multiplier -= 0.08;
		this_screen_h *= 0.08;
		
		
		srand( static_cast <int> (time( NULL )) );
		// FS --------------------------------------------------------------------------
		for( unsigned i = start; i < line.size(); i++ )
		{
			if( line[ i ] == '|' )
			{
				bufor += "*";
				string nrstr = "";
				vector <string> data;
				
				for( unsigned j = 0; j < bufor.size(); j++ )
				{
					if( bufor[ j ] == '*' )
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
				float y = con::stoi( data[ 3 ] ) *y_multiplier +this_screen_h;
				
				if( w == 4 )
				{
					if( t == type )
					{
						// Features.
						float myarmour = rand() %995 +1;
						float mydamage = 1;
						float myvelocity = 100;
						float myheartpoints = 100;
						
						foes.push_back( new Skeleton );
						foes[ foes.size() -1 ]->setPosition( x, y );
						foes[ foes.size() -1 ]->setCenterX( x );
						foes[ foes.size() -1 ]->setArmour( myarmour );
						foes[ foes.size() -1 ]->setDamage( mydamage );
						foes[ foes.size() -1 ]->setVelocity( myvelocity );
						foes[ foes.size() -1 ]->setHeartpoints( myheartpoints );
						foes[ foes.size() -1 ]->addText( L"sraka łaka kurwiarze" );
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
		
		success = true;
	}
	file.free();
	
	if( success )
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
					if( echostring[ i ] == ',' || echostring[ i ] == '.' )
					{
						lines.push_back( con::stoi( line ) );
						line = "";
						
						if( echostring[ i ] == '.' )
						{
							break;
						}
					}
					else
					{
						line += echostring[ i ];
					}
				}
				
				// Load sprites.
				for( unsigned i = 0; i < lines.size(); i++ )
				{
					sprites.push_back( new MySprite() );
					sprites[ i ]->setIdentity( "factory-sprites" );
					sprites[ i ]->load( "images/play/foes/" +name +"/" +con::itos(i) +".png", lines[ i ] );
					sprites[ i ]->setScale( screen_w /2560, screen_h /1440 );
					// printf( "%d\n", lines[ i ] );
				}
				
				for( auto &it :foes )
				{
					it->setLines( lines );
					it->setScale( screen_w /2560, screen_h /1440 );
					it->setWidth( sprites[ 0 ]->getWidth() );
				}
				
				positioning( fs_tiles, types_tiles );
				
				// Inform that everything is ok.
				ready = true;
			}
		}
	}
	
	
	// Inform that thread is ready for next action.
	thread_ready = true;
}

template <typename F>
void Factory <F>::positioning( vector <sf::Vector2f> fs, vector <sf::Uint8> types )
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
						float error_margin  = good_left -block.getWidth() -fs[ k ].x;
						if( error_margin < 0 )	error_margin = -error_margin;
						
						if( error_margin /block.getWidth() < 0.25 )
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
						float error_margin  = fs[ k ].x -good_right;
						if( error_margin < 0 )	error_margin = -error_margin;
						
						if( error_margin /block.getWidth() < 0.25 )
						{
							good_right += block.getWidth();
						}
					}
				}
			}
			
			// printf( "%f %f\n", good_left, good_right );
			foes[ i ]->setBorders( good_left, good_right );
			foes[ i ]->setPosition( foes[ i ]->getCenterX(), block_y );
			
			// delete if surface is too small
			if( good_right -good_left < block.getWidth() *2 )
			{
				foes.erase( foes.begin() +i );
				i --;
			}
		}
	}

	block.free();
}



template <typename F>
void Factory <F>::setBorderX( float x )
{
	border_x = x;
}

template <typename F>
void Factory <F>::setBorderY( float y )
{
	border_y = y;
}


template <typename F>
void Factory <F>::harm( sf::Rect <float> rect, float damage )
{
	float l;
	float r;
	float rx;
	float ry;
	float rw;
	float rh;
	
	for( unsigned i = 0; i < foes.size(); i++ )
	{
		if( foes[ i ]->isAlive() )
		{
			l = foes[ i ]->getLeft();
			r = foes[ i ]->getRight();
			rx = foes[ i ]->getRealX();
			ry = foes[ i ]->getRealY();
			rw = foes[ i ]->getRealWidth();
			rh = foes[ i ]->getRealHeight();
			
			if( rect.left +rect.width > l && rect.left < r )
			{
				if( rect.top < ry +rh && rect.top +rect.height > ry )
				{
					if( rect.top + rect.height > ry && rect.top < ry +rh )
					{
						if( rect.left + rect.width > rx && rect.left < rx +rw )
						{
							// make damage :/
							foes[ i ]->harm( damage );
						}
					}
				}
			}
		}
	}
}

template <typename F>
bool Factory <F>::isHarmed( sf::Rect <float> rect )
{
	float x, y, w, h;
	for( unsigned i = 0; i < foes.size(); i++ )
	{
		if( foes[ i ]->isAttacking() )
		{
			x = foes[ i ]->getAttackX();
			y = foes[ i ]->getAttackY();
			w = foes[ i ]->getAttackWidth();
			h = foes[ i ]->getAttackHeight();
			
			if( rect.top + rect.height > y && rect.top < y +h )
			{
				if( rect.left + rect.width > x && rect.left < x +w )
				{
					damaged = i;
					return true;
				}
			}
		}
	}
	
	return false;
}

template <typename F>
void Factory <F>::walk( sf::Rect <float> rect, double elapsedTime )
{
	float l;
	float r;
	float rx;
	float ry;
	float rw;
	float rh;
	
	for( unsigned i = 0; i < foes.size(); i++ )
	{
		if( foes[ i ]->isAlive() )
		{
			foes[ i ]->setIdle();
			
			l = foes[ i ]->getLeft();
			r = foes[ i ]->getRight();
			rx = foes[ i ]->getRealX();
			ry = foes[ i ]->getRealY();
			rw = foes[ i ]->getRealWidth();
			rh = foes[ i ]->getRealHeight();
			
			if( rect.left +rect.width > l && rect.left < r )
			{
				if( rect.top < ry +rh && rect.top +rect.height > ry )
				{
					if( foes[ i ]->ableToAppear() )
					{
						foes[ i ]->setAppear();
					}
					else if( foes[ i ]->ableToWalk() )
					{
						if( rx +rw/2 < rect.left +rect.width/2 )	foes[ i ]->turnRight();
						else										foes[ i ]->turnLeft();
						
						foes[ i ]->setWalk();
						
						if( rx +rw < r && rx +rw < rect.left && foes[ i ]->getXScale() < 0 )
						{
							foes[ i ]->moveX( elapsedTime );
						}
						else if( rx > l && rx > rect.left +rect.width  && foes[ i ]->getXScale() > 0 )
						{
							foes[ i ]->moveX( -elapsedTime );
						}
						else if( foes[ i ]->ableToAttack() )
						{
							foes[ i ]->setAttack();
						}
						else
						{
							foes[ i ]->setIdle();
						}
					}
				}
			}
		}
	}
}

template <typename F>
float Factory <F>::getDamage()
{
	return foes[ damaged ]->getDamage();
}

template class Factory <Skeleton>;