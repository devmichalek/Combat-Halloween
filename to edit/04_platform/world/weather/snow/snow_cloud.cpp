#include "04_platform/world/weather/snow/snow_cloud.h"
#include <cstdlib>


void Snow_cloud::create( string path, int screen_w, int screen_h )
{
	cloud.setName( "snow_cloud-cloud" );
	cloud.load( path );
	
	int amount = rand()%40 +50;
	for( int i = 0; i < amount; i++ )
	{
		drops.push_back( new sf::ConvexShape() );
		drops[ drops.size()-1 ]->setPointCount( 4 );
		drops[ drops.size()-1 ]->setPoint( 0, sf::Vector2f( 0, 0 ) );
		drops[ drops.size()-1 ]->setPoint( 1, sf::Vector2f( 3, 0 ) );
		drops[ drops.size()-1 ]->setPoint( 2, sf::Vector2f( 3, 3 ) );
		drops[ drops.size()-1 ]->setPoint( 3, sf::Vector2f( 0, 3 ) );
		alphas.push_back( rand()%100 +100 );
		drops[ drops.size()-1 ]->setFillColor( sf::Color( 0xFF, 0xFF, 0xFF, alphas[ alphas.size() -1 ] ) );
	}
	
	reset( screen_w, screen_h );
	// printf( "%f\n", drops[ 0 ]->getPosition().x );
}


void Snow_cloud::mechanics( int screen_w, int screen_h )
{
	x -= vel;
	cloud.setPosition( x, cloud.getY() );
	
	if( vel > 0 )
	{
		if( x +cloud.getWidth() < 0 )
		{
			// printf( "%f\n", x );
			setCloud( screen_w );
		}
	}
	else
	{
		if( x > screen_w )
		{
			// printf( "%f\n", x );
			setCloud( screen_w );
		}
	}
	
	
	for( auto &it :drops )
	{
		// printf( "%f\n", it->getPosition().x );
		it->move( 0, 1 );
		if( it->getPosition().y > screen_h )
		{
			it->setPosition( cloud.getX() +rand()%cloud.getWidth(), cloud.getY() +rand()%cloud.getHeight() );
		}
	}
}