#include "objects.h"
#include "own/file.h"

Objects::Objects()
{
	myThread = NULL;
	free();
}

Objects::~Objects()
{
	free();
}

void Objects::free()
{
	screen_w = 0;
	screen_h = 0;
	border_x = 0;
	border_y = 0;
	
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
	
	if( !fs.empty() )
	{
		fs.clear();
	}
	
	if( !types.empty() )
	{
		types.clear();
	}
	
	if( myThread != NULL )
	{
		delete myThread;
		myThread = NULL;
	}
	
	thread_ready = false;
	ready = false;
}

void Objects::reset()
{
	border_x = 0;
	border_y = 0;
	
	if( !fs.empty() )
	{
		fs.clear();
	}
	
	if( !types.empty() )
	{
		types.clear();
	}
	
	if( myThread != NULL )
	{
		delete myThread;
		myThread = NULL;
	}
	
	thread_ready = false;
	ready = false;
}

void Objects::load( float screen_w, float screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	// Load sprites.
	for( unsigned i = 0; i < 14; i++ )
	{
		sprites.push_back( new MySprite() );
		sprites[ sprites.size() -1 ]->setIdentity( "objects-sprites" );
		sprites[ sprites.size() -1 ]->load( "images/play/objects/" +con::itos(i) +".png" );
		sprites[ sprites.size() -1 ]->setScale( screen_w /2560, screen_h /1440 );
	}
}

void Objects::draw( sf::RenderWindow* &window )
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
}

void Objects::fadein( float v, int max )
{
	for( auto &it :sprites )
	{
		it->fadein( v, max );
	}
}

void Objects::fadeout( float v, int min )
{
	for( auto &it :sprites )
	{
		it->fadeout( v, min );
	}
}



bool Objects::isNull()
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

bool Objects::isReady()
{
	return ready;
}

void Objects::setThread()
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

void Objects::prepare()
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
		this_screen_h *= 0.075;
		
		
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
				
				if( w == 2 )
				{
					types.push_back( t );
					fs.push_back( sf::Vector2f( x, y ) );
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



void Objects::setBorderX( float x )
{
	border_x = x;
}

void Objects::setBorderY( float y )
{
	border_y = y;
}