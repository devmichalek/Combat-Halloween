#include "kunai_effects.h"
#include "file/file.h"

Kunai_effects::Kunai_effects()
{
	free();
}

Kunai_effects::~Kunai_effects()
{
	free();
}

void Kunai_effects::free()
{
	delay = 0;
	
	if( !offset.empty() )
	{
		offset.clear();
	}
	
	if( !lines.empty() )
	{
		lines.clear();
	}
	
	if( !active.empty() )
	{
		active.clear();
	}
	
	if( !sprites.empty() )
	{
		for( auto &it :sprites )
		{
			it->free();
		}
		
		sprites.clear();
	}
	
	if( !slabs.empty() )
	{
		for( auto &it :slabs )
		{
			it->free();
		}
		
		slabs.clear();
	}
}



void Kunai_effects::load( int which )
{
	free();
	
	delay = 8;
	
	// Set lines.
	MyFile file;
	file.load( "data/txt/skill/kunai_effects_lines.txt" );
	if( file.is_good() )
	{
		string line;
		while( file.get() >> line )
		{
			lines.push_back( con::stoi( line ) );
		}
	}
	file.free();
	
	
	
	for( unsigned i = 0; i < 3; i++ )
	{
		sprites.push_back( new MySprite() );
		sprites[ sprites.size() -1 ]->setName( "kunai_effects-sprite" );
		offset.push_back( 0 );
		active.push_back( false );
		slabs.push_back( new Slab() );
		slabs[ slabs.size() -1 ]->setName( "kunai_effects-slab" );
	}
	
	string path = "data/platform/hero/kunai_effects/";
	sprites[ 0 ]->load( path +"0.png", lines[ 0 ] );
	sprites[ 1 ]->load( path +"1.png", lines[ 1 ] );
	sprites[ 2 ]->load( path +con::itos( which ) +".png", lines[ 2 ] );
	
	// set scale.
	for( auto &it :sprites )
	{
		it->setScale( 0.9, 0.9 );
	}
	
	string path2 = "data/platform/hero/kunai_effects/sounds/";
	slabs[ 0 ]->load( path2 +"0.wav" );
	slabs[ 1 ]->load( path2 +"1.wav" );
	slabs[ 2 ]->load( path2 +"2.wav" );
}

void Kunai_effects::draw( sf::RenderWindow* &window )
{
	for( unsigned i = 0; i < sprites.size(); i++ )
	{
		if( active[ i ] )
		{
			window->draw( sprites[ i ]->get() );
		}
	}
}

void Kunai_effects::mechanics()
{
	for( unsigned i = 0; i < sprites.size(); i++ )
	{
		if( active[ i ] )
		{
			offset[ i ] ++;
			if( offset[ i ] == lines[ i ] *delay )
			{
				offset[ i ] = 0;
				active[ i ] = false;
			}
			
			sprites[ i ]->setOffset( offset[ i ] /delay );
		}
	}
}



void Kunai_effects::fadein( int v, int max )
{
	for( auto &it :sprites )
	{
		it->fadein( v, max );
	}
}

void Kunai_effects::fadeout( int v, int min )
{
	for( unsigned i = 0; i < sprites.size(); i++ )
	{
		if( active[ i ] )
		{
			sprites[ i ]->fadeout( v, min );
		}
	}
}



void Kunai_effects::run( int which, Rect* rect )
{
	if( rect != NULL )
	{
		sprites[ which ]->setPosition( rect->getX() +rect->getWidth()/2 -sprites[ which ]->getWidth() /2,
									   rect->getY() +rect->getHeight()/2 -sprites[ which ]->getHeight()/2 );
		active[ which ] = true;
		
		if( !slabs.empty() )
		{
			if( slabs[ which ]->isPlayable() )
			{
				slabs[ which ]->play();
			}
		}
	}
}



void Kunai_effects::moveX( float vel )
{
	for( unsigned i = 0; i < sprites.size(); i++ )
	{
		if( active[ i ] )
		{
			sprites[ i ]->setPosition( sprites[ i ]->getX() +vel, sprites[ i ]->getY() );
		}
	}
}

void Kunai_effects::undoFall( sf::Uint8 add )
{
	for( unsigned i = 0; i < sprites.size(); i++ )
	{
		if( active[ i ] )
		{
			sprites[ i ]->setPosition( sprites[ i ]->getX() +add, sprites[ i ]->getY() );
		}
	}
}

void Kunai_effects::setColor( sf::Color color )
{
	for( auto &it :sprites )
	{
		it->setColor( color );
	}
}



void Kunai_effects::turn()
{
	if( !slabs.empty() )
	{
		for( auto &it :slabs )
		{
			it->turn();
		}
	}
}

void Kunai_effects::turnOn()
{
	if( !slabs.empty() )
	{
		for( auto &it :slabs )
		{
			it->turnOn();
		}
	}
}

void Kunai_effects::turnOff()
{
	if( !slabs.empty() )
	{
		for( auto &it :slabs )
		{
			it->turnOff();
		}
	}
}

void Kunai_effects::setVolume( int v )
{
	if( !slabs.empty() )
	{
		for( auto &it :slabs )
		{
			it->setVolume( v );
		}
	}
}
