#include "04_platform/world/weather/snow/snow.h"
#include <cstdlib>

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
	scope = 0;
	
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

void Snow::reset()
{
	for( auto &it :drops )
	{
		it->setPosition( rand()%static_cast <int> (screen_w*1.2), rand()%screen_h );
	}
}



void Snow::load( int screen_w, int screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	scope = 50;
	int size = 80;
	
	for( int i = 0; i < size; i++ )
	{
		drops.push_back( new sf::CircleShape() );
		drops[ drops.size()-1 ]->setRadius( rand() %3 +1 );
		alphas.push_back( rand()%100 +125 );
		drops[ drops.size()-1 ]->setFillColor( sf::Color( 0xFF, 0xFF, 0xFF, alphas[ alphas.size() -1 ] ) );
	}
	
	reset();
}

void Snow::draw( sf::RenderWindow* &window )
{
	for( auto &it :drops )
	{
		window->draw( *it );
	}
}



void Snow::fadein( int v, int max )
{
	
}

void Snow::fadeout( int v, int min )
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



void Snow::mechanics()
{
	for( unsigned i = 0; i < drops.size(); i++ )
	{
		drops[ i ]->setPosition( drops[ i ]->getPosition().x -0.7, drops[ i ]->getPosition().y +3 );
		
		if( drops[ i ]->getPosition().x < 0 || drops[ i ]->getPosition().y > screen_h )
		{
			drops[ i ]->setPosition( rand()%static_cast <int> (screen_w*1.2), -rand()%screen_h/3 );
		}
	}
}
