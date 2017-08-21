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
	left = 0;
	right = 0;
	
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



void Tiles::load( float screen_w, float screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	float scale_x = screen_w /2560;
	float scale_y = screen_h /1440;
	
	// Load sprites.
	for( unsigned i = 0; i < 16; i++ )
	{
		sprites.push_back( new MySprite() );
		sprites[ sprites.size() -1 ]->setIdentity( "tiles-sprites" );
		sprites[ sprites.size() -1 ]->load( "images/play/tiles/" +con::itos(i) +".png" );
		sprites[ sprites.size() -1 ]->setScale( scale_x, scale_y );
	}
}

void Tiles::draw( sf::RenderWindow* &window )
{
	if( ready )
	{
		for( unsigned i = 0; i < types.size(); i++ )
		{
			sprites[ types[ i ] ]->setPosition( fs[ i ].x, fs[ i ].y );
			window->draw( sprites[ types[ i ] ]->get() );
		}
	}
}



void Tiles::fadein( float v, int max )
{
	if( ready )
	{
		for( auto &it :sprites )
		{
			it->fadein( v, max );
		}
	}
}

void Tiles::fadeout( float v, int min )
{
	if( ready )
	{
		for( auto &it :sprites )
		{
			it->fadeout( v, min );
		}
	}
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
			myThread = new std::thread( [=] { setTiles(); } );	// interesting.
			myThread->detach();
		}
	}
}

void Tiles::setTiles()
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
			
			if( con::stoi( mydata[ 0 ] ) == 1 )
			{
				types.push_back( con::stoi( mydata[ 1 ] ) );
				fs.push_back( sf::Vector2f( con::stof( mydata[ 2 ] ) *x_multiplier, con::stof( mydata[ 3 ] ) *y_multiplier ) );
			}
		}
		
		// Set borders.
		left = fs[ 0 ].x;
		right = fs[ fs.size() -1 ].x;
		
		// Prepare.
		ready = true;
	}
	file.free();
	
	thread_ready = true;
}

float Tiles::getLeft()
{
	return left;
}

float Tiles::getRight()
{
	return right;
}