#include "04_platform/world/weather/snow/snow.h"

Snow::Snow()
{
	free();
}

Snow::~Snow()
{
	free();
}

void Snow::free()
{
	screen_w = 0;
	screen_h = 0;
	
	if( !clouds.empty() )
	{
		for( auto &it :clouds )
		{
			it->free();
		}
		
		clouds.clear();
	}
}

void Snow::reset()
{
	for( auto &it :clouds )
	{
		it->reset( screen_w, screen_h );
	}
}



void Snow::load( int screen_w, int screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	int cloud_amount = 10;
	
	for( int i = 0; i < cloud_amount; i++ )
	{
		clouds.push_back( new Snow_cloud() );
		clouds[ clouds.size() -1 ]->create( "data/04_platform/world/0/clouds/" 
		+to_string( i ) +".png", screen_w, screen_h );
	}
}

void Snow::draw( sf::RenderWindow* &window )
{
	for( auto &it :clouds )
	{
		if( it->getX() +it->getWidth() > 0 && it->getX() < screen_w )
		{
			it->draw( window );
		}
	}
}



void Snow::fadein( int v, int max )
{
	for( auto &it :clouds )
	{
		it->fadein( v, max );
	}
}

void Snow::fadeout( int v, int min )
{
	for( auto &it :clouds )
	{
		it->fadeout( v, min );
	}
}



void Snow::mechanics()
{
	for( auto &it :clouds )
	{
		it->mechanics( screen_w, screen_h );
	}
}

void Snow::moveX( sf::Uint8 direction, float vel )
{
	if( direction == 1 )
	{
		for( auto &it :clouds )
		{
			it->moveX( vel );
		}
	}
	else if( direction == 2 )
	{
		for( auto &it :clouds )
		{
			it->moveX( -vel );
		}
	}
}

void Snow::undoFall( sf::Uint8 add )
{
	for( auto &it :clouds )
	{
		it->moveX( add );
	}
}