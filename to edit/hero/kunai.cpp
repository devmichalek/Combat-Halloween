#include "hero/kunai.h"

Kunai::Kunai()
{
	scale = 0;
}

Kunai::~Kunai()
{
	free();
}

void Kunai::free()
{
	sprite.free();
	
	for( unsigned i = 0; i < b.size(); i++ )
	{
		b[ i ]->free();
	}
	
	b.clear();
	
	scale = 0;
}

	
void Kunai::load()
{
	scale = 1;
	
	sprite.setName( "kunai-sprite" );
	sprite.load( "data/sprites/hero/0.png" );
	
	for( int i = 0; i < 6; i++ )
	{
		b.push_back( new Bit() );
	}
}

void Kunai::draw( sf::RenderWindow* &window )
{
	for( unsigned i = 0; i < b.size(); i++ )
	{
		if( b[ i ]->isActive() )
		{
			b[ i ]->go();
			sprite.setPosition( b[ i ]->getX(), b[ i ]->getY() );
			
			if( b[ i ]->getVel() < 0 )
			{
				sprite.setScale( scale, scale );
			}
			else if( b[ i ]->getVel() > 0 )
			{
				sprite.setScale( -scale, scale );
			}
			
			window->draw( sprite.get() );
		}
	}
}

void Kunai::throwing( int x, int y, int vel )
{
	for( unsigned i = 0; i < b.size(); i++ )
	{
		if( !b[ i ]->isActive() )
		{
			b[ i ]->start( vel, x, y );
			break;
		}
	}
}

unsigned int Kunai::getNr()
{
	return b.size();
}

int Kunai::getX( int which )
{
	int x = b[ which ]->getX();
	
	return x;
}

int Kunai::getY( int which )
{
	return b[ which ]->getY();
}

int Kunai::getW()
{
	/*
	int w = sprite.getWidth();
	if( w < 0 )
		w = -w;
	*/
		
	return 1;
}

int Kunai::getH()
{
	return sprite.getHeight();
}

void Kunai::destroy( int which )
{
	b[ which ]->reset();
}

void Kunai::fadein( int v, int max )
{
	sprite.fadein( v, max );
}

void Kunai::fadeout( int v, int min )
{
	sprite.fadein( v, min );
}