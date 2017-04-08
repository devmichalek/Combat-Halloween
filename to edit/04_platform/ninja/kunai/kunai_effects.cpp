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
	
	if( !x.empty() )
	{
		x.clear();
	}
	
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
		x.push_back( 0 );
		offset.push_back( 0 );
		active.push_back( false );
	}
	
	string path = "data/04_platform/hero/kunai_effects/";
	sprites[ 0 ]->load( path +"0.png", lines[ 0 ] );
	sprites[ 1 ]->load( path +"1.png", lines[ 1 ] );
	sprites[ 2 ]->load( path +con::itos( which ) +".png", lines[ 2 ] );
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
		// then
		this->x[ which ] = rect->getX() +rect->getWidth()/2 -sprites[ which ]->getWidth() /2;
		sprites[ which ]->setPosition( this->x[ which ], rect->getY() +rect->getHeight()/2 -sprites[ which ]->getHeight()/2 );
		active[ which ] = true;
	}
}



void Kunai_effects::moveX( float vel )
{
	for( unsigned i = 0; i < sprites.size(); i++ )
	{
		if( active[ i ] )
		{
			x[ i ] += vel;
			sprites[ i ]->setPosition( x[ i ], sprites[ i ]->getY() );
		}
	}
}

void Kunai_effects::undoFall( sf::Uint8 add )
{
	for( unsigned i = 0; i < sprites.size(); i++ )
	{
		if( active[ i ] )
		{
			x[ i ] += add;
			sprites[ i ]->setPosition( x[ i ], sprites[ i ]->getY() );
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