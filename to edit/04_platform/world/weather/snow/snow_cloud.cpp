#include "04_platform/world/weather/snow/snow_cloud.h"
#include <cstdlib>

void Snow_cloud::free()
{
	x = 0;
	vel = 0;
	
	cloud.free();
	
	if( !alphas.empty() )
	{
		alphas.clear();
	}
	
	if( !drops.empty() )
	{
		for( auto &it :drops )
		{
			delete it;
		}
		
		drops.clear();
	}
}

void Snow_cloud::reset( int screen_w, int screen_h )
{
	setVel();
	x = static_cast <float> ( rand()%screen_w ) ;
	
	cloud.setPosition( x, -rand()%40 );
	for( auto &it :drops )
	{
		it->setPosition( x +rand()%cloud.getWidth(), cloud.getY() +rand()%screen_h );
	}
}

void Snow_cloud::draw( sf::RenderWindow* &window )
{
	for( auto &it :drops )
	{
		window->draw( *it );
	}
	
	window->draw( cloud.get() );
}

void Snow_cloud::fadeout( int v, int min )
{
	cloud.fadeout( v, min );
	
	for( auto &it :alphas )
	{
		it -= v;
		if( it < min )
		{
			it = min;
			if( it < 0 )
			{
				it = 0;
			}
		}
	}
	
	for( unsigned i = 0; i < drops.size(); i++ )
	{
		sf::Color c = drops[ i ]->getFillColor();
		c.a = alphas[ i ];
		drops[ i ]->setFillColor( c );
	}
}

void Snow_cloud::create( string path, int screen_w, int screen_h )
{
	cloud.setName( "snow_cloud-cloud" );
	cloud.load( path );
	
	int amount = rand()%40 +20;
	for( int i = 0; i < amount; i++ )
	{
		drops.push_back( new sf::CircleShape( static_cast <float> (rand()%3 +1) ) );
		alphas.push_back( rand()%100 +100 );
		drops[ drops.size()-1 ]->setFillColor( sf::Color( 0xFF, 0xFF, 0xFF, alphas[ alphas.size() -1 ] ) );
	}
	
	reset( screen_w, screen_h );
	
	// printf( "%d\n", drops.size() );
	// printf( "%f  %f  %f\n", drops[ 0 ]->getPosition().x, drops[ 0 ]->getPosition().y, drops[ 0 ]->getRadius() );
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

void Snow_cloud::moveX( int add )
{
	x += add;
	cloud.setPosition( x, cloud.getY() );
	for( auto &it :drops )
	{
		it->setPosition( it->getPosition().x +add, it->getPosition().y );
	}
	
	// printf( "--%d\n", drops.size() );
	// printf( "%f %f\n", drops[ 0 ]->getPosition().x, drops[ 0 ]->getPosition().y );
}