#include "tiles.h"
#include "own/file.h"

Tiles::Tiles()
{
	myThread = NULL;
	free();
}

Tiles::~Tiles()
{
	free();
}

void Tiles::free()
{
	screen_w = 0;
	screen_h = 0;
	border_x = 0;
	border_y = 0;
	fadingout = false;
	
	if( !fs.empty() )
	{
		fs.clear();
	}
	
	if( !types.empty() )
	{
		types.clear();
	}
	
	if( !ufs.empty() )
	{
		ufs.clear();
	}
	
	if( !utypes.empty() )
	{
		utypes.clear();
	}
	
	if( !ualpha.empty() )
	{
		ualpha.clear();
	}
	
	if( myThread != NULL )
	{
		delete myThread;
		myThread = NULL;
	}
	
	thread_ready = false;
	ready = false;
}

void Tiles::reset()
{
	border_x = 0;
	border_y = 0;
	fadingout = false;
	
	if( !fs.empty() )
	{
		fs.clear();
	}
	
	if( !types.empty() )
	{
		types.clear();
	}
	
	if( !ufs.empty() )
	{
		ufs.clear();
	}
	
	if( !utypes.empty() )
	{
		utypes.clear();
	}
	
	if( !ualpha.empty() )
	{
		ualpha.clear();
	}
	
	if( myThread != NULL )
	{
		delete myThread;
		myThread = NULL;
	}
	
	thread_ready = false;
	ready = false;
}

void Tiles::load( float screen_w, float screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	// Load sprites.
	for( unsigned i = 0; i < 17; i++ )
	{
		sprites.push_back( new MySprite() );
		sprites[ sprites.size() -1 ]->setIdentity( "tiles-sprites" );
		sprites[ sprites.size() -1 ]->load( "images/play/tiles/" +con::itos(i) +".png" );
		sprites[ sprites.size() -1 ]->setScale( screen_w /2560, screen_h /1440 );
	}
}

void Tiles::draw( sf::RenderWindow* &window )
{
	for( unsigned i = 0; i < fs.size(); i++ )
	{
		if( fs[ i ].x < border_x +screen_w && fs[ i ].y < border_y +screen_h )
		{
			if( fs[ i ].x +sprites[ types[ i ] ]->getWidth() > border_x && fs[ i ].y +sprites[ types[ i ] ]->getHeight() > border_y )
			{
				sprites[ types[ i ] ]->setPosition( fs[ i ].x, fs[ i ].y );
				window->draw( sprites[ types[ i ] ]->get() );
			}
		}
	}
	
	if( !fadingout )
	{
		for( unsigned i = 0; i < ualpha.size(); i++ )
		{
			if( ualpha[ i ] > 0 )
			{
				if( ufs[ i ].x < border_x +screen_w && ufs[ i ].y < border_y +screen_h )
				{
					if( ufs[ i ].x +sprites[ utypes[ i ] ]->getWidth() > border_x && ufs[ i ].y +sprites[ utypes[ i ] ]->getHeight() > border_y )
					{
						float alpha = sprites[ utypes[ i ] ]->getAlpha();
						sprites[ utypes[ i ] ]->setAlpha( ualpha[ i ] );
						sprites[ utypes[ i ] ]->setPosition( ufs[ i ].x, ufs[ i ].y );
						window->draw( sprites[ utypes[ i ] ]->get() );
						sprites[ utypes[ i ] ]->setAlpha( alpha );
					}
				}
			}
		}
	}
}

void Tiles::fadein( float v, int max )
{
	for( auto &it :sprites )
	{
		it->fadein( v, max );
	}
	
	fadingout = false;
}

void Tiles::fadeout( float v, int min )
{
	for( auto &it :sprites )
	{
		it->fadeout( v, min );
	}
	
	fadingout = true;
}



bool Tiles::isNull()
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

bool Tiles::isReady()
{
	return ready;
}

void Tiles::setThread()
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

void Tiles::prepare()
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
				
				if( w == 0 )
				{
					types.push_back( t );
					fs.push_back( sf::Vector2f( x, y ) );
				}
				else if( w == 1 )
				{
					utypes.push_back( t );
					ufs.push_back( sf::Vector2f( x, y ) );
					ualpha.push_back( 0 );
				}
				
				// Clear.
				bufor = "";
			}
			else
			{
				bufor += line[ i ];
			}
		}
		
		// Inform that everything is ok.
		ready = true;
	}
	file.free();
	
	// Inform that thread is ready for next action.
	thread_ready = true;
}



bool Tiles::checkCollisionRect( sf::Rect <float> rect )
{
	// The rest.
	float x;
	float y;
	sf::Uint8 t;
	
	// Visible tiles.
	for( unsigned i = 0; i < fs.size(); i++ )
	{
		x = fs[ i ].x;
		y = fs[ i ].y;
		t = types[ i ];
		
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
	
	// Unvisible tiles.
	for( unsigned i = 0; i < ufs.size(); i++ )
	{
		x = ufs[ i ].x;
		y = ufs[ i ].y;
		t = utypes[ i ];
		
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

void Tiles::tickGravity( sf::Rect <float> rect, double elapsedTime )
{
	// The rest.
	float x;
	float y;
	sf::Uint8 t;
	
	// Unvisible tiles but for alpha.
	for( unsigned i = 0; i < ufs.size(); i++ )
	{
		x = ufs[ i ].x;
		y = ufs[ i ].y;
		t = utypes[ i ];
		
		if( ualpha[ i ] > 0 )
		{
			ualpha[ i ] -= elapsedTime *0xFF/2;
		}
		
		if( x < border_x +screen_w && y < border_y +screen_h )
		{
			if( x +sprites[ t ]->getWidth() > border_x && y +sprites[ t ]->getHeight() > border_y )
			{
				sprites[ t ]->setPosition( x, y );
				if( sprites[ t ]->checkCollisionRect( rect ) )
				{
					if( ualpha[ i ] < 0xFF )
					{
						ualpha[ i ] += elapsedTime *0xFF;
					}
				}
			}
		}
	}
}

void Tiles::setBorderX( float x )
{
	border_x = x;
}

void Tiles::setBorderY( float y )
{
	border_y = y;
}

float Tiles::getBorderX()
{
	return border_x;
}

float Tiles::getBorderY()
{
	return border_y;
}

float Tiles::getScreenWidth()
{
	return screen_w;
}

float Tiles::getScreenHeight()
{
	return screen_h;
}