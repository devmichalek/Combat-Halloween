#include "04_platform/world/weather/rain/rain.h"

Rain::Rain()
{
	free();
}

Rain::~Rain()
{
	free();
}

void Rain::free()
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

void Rain::reset()
{
	for( auto &it :clouds )
	{
		it->reset( screen_w, screen_h );
	}
}



void Rain::load( int screen_w, int screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	int cloud_amount = 10;
	
	for( int i = 0; i < cloud_amount; i++ )
	{
		clouds.push_back( new Rain_cloud() );
		clouds[ clouds.size() -1 ]->create( "data/04_platform/world/0/clouds/" 
		+to_string( i ) +".png", screen_w, screen_h );
	}
}

void Rain::draw( sf::RenderWindow* &window )
{
	for( auto &it :clouds )
	{
		if( it->getX() +it->getWidth() > 0 && it->getX() < screen_w )
		{
			it->draw( window );
		}
	}
}



void Rain::fadein( int v, int max )
{
	for( auto &it :clouds )
	{
		it->fadein( v, max );
	}
}

void Rain::fadeout( int v, int min )
{
	for( auto &it :clouds )
	{
		it->fadeout( v, min );
	}
}



void Rain::mechanics()
{
	for( auto &it :clouds )
	{
		it->mechanics( screen_w, screen_h );
	}
}

void Rain::moveX( sf::Uint8 direction, float vel )
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

void Rain::undoFall( sf::Uint8 add )
{
	for( auto &it :clouds )
	{
		it->moveX( add );
	}
}