#include "04_platform/enemy/flying/fly_factory.h"
#include "file/file.h"

Fly_factory::Fly_factory()
{
	free();
}

Fly_factory::~Fly_factory()
{
	free();
}

void Fly_factory::free()
{
	if( !flies.empty() )
	{
		for( auto &it :flies )
		{
			it->free();
		}
		
		flies.clear();
	}
}

void Fly_factory::reset()
{
	for( auto &it :flies )
	{
		it->reset();
	}
}



void Fly_factory::load( int type, int screen_w, int screen_h )
{
	free();
	
	vector <string> strs;
	// Set stuff.
	MyFile file;
	file.load( "data/txt/enemy/flying/" +con::itos(type) +".txt" );
	if( file.is_good() )
	{
		string line;
		while( file.get() >> line )
		{
			strs.push_back( line );
		}
		
		for( unsigned i = 0; i < strs.size(); i++ )
		{
			flies.push_back( new Fly() );
			flies[ flies.size() -1 ]->load( screen_w, screen_h, con::itos(type) +"/" +strs[ i ] );
		}
	}
	file.free();
}

void Fly_factory::draw( sf::RenderWindow* &window )
{
	for( auto &it :flies )
	{
		it->draw( window );
	}
}



void Fly_factory::fadein( int j, int max )
{
	for( auto &it :flies )
	{
		it->fadein( j, max );
	}
}

void Fly_factory::fadeout( int j, int min )
{
	for( auto &it :flies )
	{
		it->fadeout( j, min );
	}
}




void Fly_factory::moveX( sf::Uint8 d, float v )
{
	for( auto &it :flies )
	{
		it->moveX( d, v );
	}
}

void Fly_factory::undoFall( sf::Uint8 add )
{
	for( auto &it :flies )
	{
		it->undoFall( add );
	}
}

void Fly_factory::mechanics()
{
	for( auto &it :flies )
	{
		it->mechanics();
	}
}

void Fly_factory::setColor( sf::Color color )
{
	for( auto &it :flies )
	{
		it->setColor( color );
	}
}