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



void Coins::load( float screen_w, float screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	float scale_x = screen_w /2560;
	float scale_y = screen_h /1440;
	
	// Load sprite.
	line = 7;
	sprite.setIdentity( "coins-sprite" );
	sprite.load( "images/play/coin.png", line );
	sprite.setScale( scale_x, scale_y );
}

void Coins::draw( sf::RenderWindow* &window )
{
	if( ready )
	{
		for( unsigned i = 0; i < fs.size(); i++ )
		{
			sprite.setPosition( fs[ i ].x, fs[ i ].y );
			sprite.setOffset( static_cast <int> (offsets[ i ]) );
			window->draw( sprite.get() );
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
	if( ready )
	{
		sprite.fadein( v, max );
	}
}

void Coins::fadeout( float v, int min )
{
	if( ready )
	{
		sprite.fadeout( v, min );
	}
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
			myThread = new std::thread( [=] { setCoins(); } );	// interesting.
			myThread->detach();
		}
	}
}

void Coins::setCoins()
{
	MyFile file;
	file.load( "txt/worlds/world_.txt" );
	if( file.is_good() )
	{
		string myline = "";
		
		// Set multipliers.
		getline( file.get(), myline );
		float x_multiplier = screen_w /con::stof( myline );
		getline( file.get(), myline );
		float y_multiplier = screen_h /con::stof( myline );
		
		// Set seed.
		srand( static_cast <int> (time( NULL )) );
		
		while( getline( file.get(), myline ) )
		{
			vector <string> mydata;
			string mynumber = "";
			
			for( unsigned i = 0; i < myline.size(); i++ )
			{
				if( myline[ i ] == '.' )
				{
					mydata.push_back( mynumber );
					mynumber = "";
					i++;
				}
				
				mynumber += myline[ i ];
			}
			mydata.push_back( mynumber );
			
			if( con::stoi( mydata[ 0 ] ) == 0 )
			{
				fs.push_back( sf::Vector2f( con::stof( mydata[ 2 ] ) *x_multiplier, con::stof( mydata[ 3 ] ) *y_multiplier ) );
				offsets.push_back( rand() %line );
			}
		}
		
		ready = true;
	}
	file.free();
	
	thread_ready = true;
}