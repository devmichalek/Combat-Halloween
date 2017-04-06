#include "skulls.h"
#include "file/file.h"

Skulls::Skulls()
{
	free();
}

Skulls::~Skulls()
{
	free();
}

void Skulls::free()
{
	if( !skulls.empty() )
	{
		for( auto &it :skulls )
		{
			it->free();
		}
		
		skulls.clear();
	}
}

void Skulls::reset()
{
	for( auto &it :skulls )
	{
		it->reset();
	}
}



void Skulls::load( int type, int screen_w, int screen_h )
{
	free();
	
	vector <string> strs;
	// Set stuff.
	MyFile file;
	file.load( "data/txt/enemy/skulls/" +con::itos(type) +".txt" );
	if( file.is_good() )
	{
		string line;
		while( file.get() >> line )
		{
			strs.push_back( line );
		}
		
		for( unsigned i = 0; i < strs.size(); i++ )
		{
			skulls.push_back( new Skull() );
			skulls[ skulls.size() -1 ]->load( screen_w, screen_h, con::itos(type) +"/" +strs[ i ] );
		}
	}
	file.free();
}

void Skulls::draw( sf::RenderWindow* &window )
{
	for( auto &it :skulls )
	{
		it->draw( window );
	}
}



void Skulls::fadein( int j, int max )
{
	for( auto &it :skulls )
	{
		it->fadein( j, max );
	}
}

void Skulls::fadeout( int j, int min )
{
	for( auto &it :skulls )
	{
		it->fadeout( j, min );
	}
}




void Skulls::moveX( sf::Uint8 d, float v )
{
	for( auto &it :skulls )
	{
		it->moveX( d, v );
	}
}

void Skulls::undoFall( sf::Uint8 add )
{
	for( auto &it :skulls )
	{
		it->undoFall( add );
	}
}

void Skulls::mechanics( int x, int y )
{
	for( auto &it :skulls )
	{
		it->mechanics( x, y );
	}
}

void Skulls::setColor( sf::Color color )
{
	for( auto &it :skulls )
	{
		it->setColor( color );
	}
}