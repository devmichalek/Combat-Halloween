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



void Objects::load( float screen_w, float screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	float scale_x = screen_w /2560;
	float scale_y = screen_h /1440;
	
	// Load sprites.
	for( unsigned i = 0; i < 14; i++ )
	{
		sprites.push_back( new MySprite() );
		sprites[ sprites.size() -1 ]->setIdentity( "objects-sprites" );
		sprites[ sprites.size() -1 ]->load( "images/play/objects/" +con::itos(i) +".png" );
		sprites[ sprites.size() -1 ]->setScale( scale_x, scale_y );
	}
}

void Objects::draw( sf::RenderWindow* &window )
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



void Objects::fadein( float v, int max )
{
	if( ready )
	{
		for( auto &it :sprites )
		{
			it->fadein( v, max );
		}
	}
}

void Objects::fadeout( float v, int min )
{
	if( ready )
	{
		for( auto &it :sprites )
		{
			it->fadeout( v, min );
		}
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
			myThread = new std::thread( [=] { setObjects(); } );	// interesting.
			myThread->detach();
		}
	}
}

void Objects::setObjects()
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
			
			if( con::stoi( mydata[ 0 ] ) == 2 )
			{
				types.push_back( con::stoi( mydata[ 1 ] ) );
				fs.push_back( sf::Vector2f( con::stof( mydata[ 2 ] ) *x_multiplier, con::stof( mydata[ 3 ] ) *y_multiplier ) );
			}
		}
		
		ready = true;
	}
	file.free();
	
	thread_ready = true;
}