#include "04_platform/world/weather/wind/wind.h"
#include <cstdlib>

Wind::Wind()
{
	free();
}

Wind::~Wind()
{
	free();
}

void Wind::free()
{
	screen_w = 0;
	screen_h = 0;
	scope = 0;
	
	if( !ways.empty() )
	{
		ways.clear();
	}
	
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

void Wind::reset()
{
	for( auto &it :ways )
	{
		it = rand() %scope;
		if( rand() %2 == 1 )
		{
			it *= -1;
		}
	}
	
	for( auto &it :drops )
	{
		it->setPosition( rand()%(screen_w*2), rand()%screen_h );
	}
}



void Wind::create( int screen_w, int screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	scope = 50;
	int size = 200;
	
	for( int i = 0; i < size; i++ )
	{
		ways.push_back( 0 );
		
		drops.push_back( new sf::ConvexShape() );
		drops[ drops.size()-1 ]->setPointCount( 4 );
		drops[ drops.size()-1 ]->setPoint( 0, sf::Vector2f( 0, 0 ) );
		drops[ drops.size()-1 ]->setPoint( 1, sf::Vector2f( 3, 0 ) );
		drops[ drops.size()-1 ]->setPoint( 2, sf::Vector2f( 3, 3 ) );
		drops[ drops.size()-1 ]->setPoint( 3, sf::Vector2f( 0, 3 ) );
		alphas.push_back( rand()%100 +150 );
		drops[ drops.size()-1 ]->setFillColor( sf::Color( 0x8C, 0x5B, 0x00, alphas[ alphas.size() -1 ] ) );
	}
	
	reset();
}

void Wind::draw( sf::RenderWindow* &window )
{
	for( auto &it :drops )
	{
		window->draw( *it );
	}
}



void Wind::fadein( int v, int max )
{
	
}

void Wind::fadeout( int v, int min )
{
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



void Wind::mechanics()
{
	for( auto &it :ways )
	{
		if( it < 0 )
		{
			it ++;
		}
		else if( it > 0 )
		{
			it --;
		}
		else
		{
			it = rand() %scope;
			if( rand() %2 == 1 )
			{
				it *= -1;
			}
		}
	}
	
	for( unsigned i = 0; i < drops.size(); i++ )
	{
		if( drops[ i ]->getPosition().y == 0 )
		{
			ways[ i ] = rand() %scope;
		}
		else if( drops[ i ]->getPosition().y == screen_h )
		{
			ways[ i ] = rand() %scope * -1;
		}
		
		drops[ i ]->setPosition( drops[ i ]->getPosition().x -3, drops[ i ]->getPosition().y +(ways[ i ] < 0 ? -1 : 1) );
		
		if( drops[ i ]->getPosition().x < -screen_w )
		{
			drops[ i ]->setPosition( screen_w +rand()%screen_w, rand()%screen_h );
		}
	}
}

void Wind::moveX( sf::Uint8 direction, float vel )
{
	if( direction == 1 )
	{
		for( auto &it :drops )
		{
			it->setPosition( it->getPosition().x +vel, it->getPosition().y );
		}
	}
	else if( direction == 2 )
	{
		for( auto &it :drops )
		{
			it->setPosition( it->getPosition().x -vel, it->getPosition().y );
		}
	}
}

void Wind::undoFall( sf::Uint8 add )
{
	for( auto &it :drops )
	{
		it->setPosition( it->getPosition().x +add, it->getPosition().y );
	}
}
