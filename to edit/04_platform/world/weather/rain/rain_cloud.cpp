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

void Rain_cloud::reset( int screen_w, int screen_h )
{
	setVel();
	x = static_cast <float> ( rand()%screen_w ) ;
	
	cloud.setPosition( x, -rand()%40 );
	for( auto &it :drops )
	{
		it->setPosition( x +rand()%cloud.getWidth(), cloud.getY() +rand()%screen_h );
	}
}



void Rain_cloud::create( string path, int screen_w, int screen_h )
{
	cloud.setName( "rain_cloud-cloud" );
	cloud.load( path );
	
	int amount = rand()%50 +20;
	for( int i = 0; i < amount; i++ )
	{
		drops.push_back( new sf::ConvexShape() );
		drops[ drops.size()-1 ]->setPointCount( 4 );
		drops[ drops.size()-1 ]->setPoint( 0, sf::Vector2f( 0, 0 ) );
		drops[ drops.size()-1 ]->setPoint( 1, sf::Vector2f( 2, 0 ) );
		drops[ drops.size()-1 ]->setPoint( 2, sf::Vector2f( 2, 2 ) );
		drops[ drops.size()-1 ]->setPoint( 3, sf::Vector2f( 0, 2 ) );
		alphas.push_back( rand()%100 +100 );
		drops[ drops.size()-1 ]->setFillColor( sf::Color( 0x11, 0x11, 0x11, alphas[ alphas.size() -1 ] ) );
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





void Rain_cloud::mechanics( int screen_w, int screen_h )
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
		it->move( 0, 3 );
		if( it->getPosition().y > screen_h )
		{
			it->setPosition( cloud.getX() +rand()%cloud.getWidth(), cloud.getY() +rand()%cloud.getHeight() );
		}
	}
}

void Rain_cloud::moveX( int add )
{
	x += add;
	cloud.setPosition( x, cloud.getY() );
	for( auto &it :drops )
	{
		it->setPosition( it->getPosition().x +add, it->getPosition().y );
	}
}



int Rain_cloud::getX()
{
	return x;
}

int Rain_cloud::getWidth()
{
	return cloud.getWidth();
}

void Rain_cloud::setCloud( int screen_w )
{
	setVel();
	
	if( vel > 0 )
	{
		x = static_cast <float> ( rand()%screen_w +screen_w ) ;
	}
	else
	{
		x = static_cast <float> ( (rand()%screen_w) *-1 ) ;
	}
	
	cloud.setPosition( x, -rand()%40 );
}

void Rain_cloud::setVel()
{
	int result = 1;
	if( rand()%2 == 1 )
	{
		result = -1;
	}
	
	vel = static_cast <float> (rand()%40 +40) /100;
	vel *= result;
}