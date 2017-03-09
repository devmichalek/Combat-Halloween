#include "04_platform/world/weather/rain/rain_cloud.h"
#include <cstdlib>

Rain_cloud::Rain_cloud()
{
	free();
}

Rain_cloud::~Rain_cloud()
{
	free();
}

void Rain_cloud::free()
{
	cloud.free();
	if( !drops.empty() )
	{
		for( auto &it :drops )
		{
			delete it;
		}
		
		drops.clear();
	}
}

void Rain_cloud::reset( int screen_w, int screen_h )
{
	cloud.setPosition( rand()%screen_w, -rand()%40 );
	for( auto &it :drops )
	{
		it->setPosition( cloud.getX() +rand()%cloud.getWidth(), cloud.getY() +rand()%screen_h );
	}
}



void Rain_cloud::create( string path, int screen_w, int screen_h )
{
	cloud.setName( "rain-cloud-cloud" );
	cloud.load( path );
	
	int amount = rand()%50 +50;
	for( int i = 0; i < amount; i++ )
	{
		drops.push_back( new sf::ConvexShape() );
		drops[ drops.size()-1 ]->setPointCount( 4 );
		drops[ drops.size()-1 ]->setPoint( 0, sf::Vector2f( 0, 0 ) );
		drops[ drops.size()-1 ]->setPoint( 1, sf::Vector2f( 1, 0 ) );
		drops[ drops.size()-1 ]->setPoint( 2, sf::Vector2f( 1, 1 ) );
		drops[ drops.size()-1 ]->setPoint( 3, sf::Vector2f( 0, 1 ) );
		drops[ drops.size()-1 ]->setFillColor( sf::Color( 0x11, 0x11, 0x11, rand()%100 +100 ) );
		drops[ drops.size()-1 ]->setScale( 1, rand()%6 +1 );
	}
	
	reset( screen_w, screen_h );
	// printf( "%f\n", drops[ 0 ]->getPosition().x );
}

void Rain_cloud::draw( sf::RenderWindow* &window )
{
	for( auto &it :drops )
	{
		window->draw( *it );
	}
	
	window->draw( cloud.get() );
}



void Rain_cloud::fadein( int v, int max )
{
	cloud.fadein( v, max );
}

void Rain_cloud::fadeout( int v, int min )
{
	cloud.fadeout( v, min );
	
	/*
	for( auto &it :drops )
	{
		it->fadeout( v, min );
	}
	*/
}





void Rain_cloud::mechanics( int screen_w, int screen_h )
{
	cloud.setPosition( cloud.getX() -1, cloud.getY() );
	
	if( cloud.getX() +cloud.getWidth() < 0 )
	{
		cloud.setPosition( screen_w +rand()%screen_w, -rand()%40 );
	}
	
	for( auto &it :drops )
	{
		// printf( "%f\n", it->getPosition().x );
		it->move( 0, 3 );
		if( it->getPosition().y > screen_h )
		{
			it->setPosition( cloud.getX() +rand()%cloud.getWidth(), cloud.getY() +rand()%cloud.getHeight() );
		}
	}
}

void Rain_cloud::moveX( int add )
{
	cloud.setPosition( cloud.getX() +add, cloud.getY() );
	for( auto &it :drops )
	{
		it->setPosition( it->getPosition().x +add, it->getPosition().y );
	}
}



int Rain_cloud::getX()
{
	return cloud.getX();
}

int Rain_cloud::getWidth()
{
	return cloud.getWidth();
}