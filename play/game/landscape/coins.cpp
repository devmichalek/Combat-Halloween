#include "coins.h"
#include "own/file.h"

Coins::Coins()
{
	myThread = NULL;
	free();
}

Coins::~Coins()
{
	free();
}

void Coins::free()
{
	screen_w = 0;
	screen_h = 0;
	border_x = 0;
	border_y = 0;
	
	sprite.free();
	
	if( !fs.empty() )
	{
		fs.clear();
	}
	
	if( !offsets.empty() )
	{
		offsets.clear();
	}
	
	line = 0;
	
	if( myThread != NULL )
	{
		delete myThread;
		myThread = NULL;
	}
	
	thread_ready = false;
	ready = false;
}

void Coins::reset()
{
	border_x = 0;
	border_y = 0;
	
	if( !fs.empty() )
	{
		fs.clear();
	}
	
	if( !offsets.empty() )
	{
		offsets.clear();
	}
	
	if( myThread != NULL )
	{
		delete myThread;
		myThread = NULL;
	}
	
	thread_ready = false;
	ready = false;
}

void Coins::load( float screen_w, float screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	// Load sprite.
	line = 7;
	sprite.setIdentity( "coins-sprite" );
	sprite.load( "images/play/coin.png", line );
	sprite.setScale( 0.5, 0.5 );
}

void Coins::draw( sf::RenderWindow* &window )
{
	for( unsigned i = 0; i < fs.size(); i++ )
	{
		if( fs[ i ].x < border_x +screen_w && fs[ i ].y < border_y +screen_h )
		{
			if( fs[ i ].x +sprite.getWidth() > border_x && fs[ i ].y +sprite.getHeight() > border_y )
			{
				sprite.setPosition( fs[ i ].x, fs[ i ].y );
				sprite.setOffset( static_cast <int> ( offsets[ i ] ) );
				window->draw( sprite.get() );
			}
		}
	}
}

void Coins::mechanics( double elapsedTime )
{
	for( unsigned i = 0; i < offsets.size(); i++ )
	{
		offsets[ i ] += elapsedTime *25;
		if( offsets[ i ] == line )
		{
			offsets[ i ] = 0;
		}
		else if( offsets[ i ] > line )
		{
			offsets[ i ] = static_cast <int> (offsets[ i ]) %line;
		}
	}
}

void Coins::fadein( float v, int max )
{
	sprite.fadein( v, max );
}

void Coins::fadeout( float v, int min )
{
	sprite.fadeout( v, min );
}



bool Coins::isNull()
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

bool Coins::isReady()
{
	return ready;
}

void Coins::setThread()
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

void Coins::prepare()
{
	// Inform that we end.
	thread_ready = true;
	
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
		
		
		// NEW SIZES --------------------------------------------------------------------------
		float my_screen_w = 0;
		float my_screen_h = 0;
		
		// Set my_screen_w.
		for( unsigned i = start; i < line.size(); i++ )
		{
			if( line[ i ] == '|' )
			{
				start = i +1;
				my_screen_w = screen_w -con::stof( bufor );
				bufor = "";
				break;
			}
			
			bufor += line[ i ];
		}
		
		// Set my_screen_h.
		for( unsigned i = start; i < line.size(); i++ )
		{
			if( line[ i ] == '|' )
			{
				start = i +1;
				my_screen_h = screen_h -con::stof( bufor ) +1;
				bufor = "";
				break;
			}
			
			bufor += line[ i ];
		}
		
		
		// FS --------------------------------------------------------------------------
		for( unsigned i = start; i < line.size(); i++ )
		{
			if( line[ i ] == '|' )
			{
				bufor += "*";
				string nrstr = "";
				vector <string> data;
				
				bool wrong = false;
				for( unsigned j = 0; j < bufor.size(); j++ )
				{
					if( bufor[ j ] == '*' )
					{
						if( data.size() == 0 )
						{
							if( con::stoi( nrstr ) != 3 )
							{
								wrong = true;
								break;
							}
						}
						
						data.push_back( nrstr );
						nrstr = "";
					}
					else
					{
						nrstr += bufor[ j ];
					}
				}
				
				if( !wrong )
				{
					sf::Uint8 w = con::stoi( data[ 0 ] );
					sf::Uint8 t = con::stoi( data[ 1 ] );
					float x = con::stoi( data[ 2 ] ) *0.999;
					float y = con::stoi( data[ 3 ] ) +my_screen_h;
					
					if( w == 3 )
					{
						fs.push_back( sf::Vector2f( x, y ) );
						offsets.push_back( rand() %this->line );
					}
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



void Coins::setBorderX( float x )
{
	border_x = x;
}

void Coins::setBorderY( float y )
{
	border_y = y;
}