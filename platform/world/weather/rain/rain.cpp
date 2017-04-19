#include "rain.h"
#include <cstdlib>

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

void Rain::reset()
{
	for( auto &it :drops )
	{
		it->setPosition( rand()%static_cast <int> (screen_w*1.2), rand()%screen_h );
	}
}



void Rain::load( int screen_w, int screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	scope = 50;
	int size = 80;
	
	for( int i = 0; i < size; i++ )
	{
		drops.push_back( new sf::ConvexShape() );
		drops[ drops.size()-1 ]->setPointCount( 4 );
		drops[ drops.size()-1 ]->setPoint( 0, sf::Vector2f( 0, 0 ) );
		drops[ drops.size()-1 ]->setPoint( 1, sf::Vector2f( 2, 0 ) );
		drops[ drops.size()-1 ]->setPoint( 2, sf::Vector2f( 2, 2 ) );
		drops[ drops.size()-1 ]->setPoint( 3, sf::Vector2f( 0, 2 ) );
		alphas.push_back( rand()%100 +150 );
		
		drops[ drops.size()-1 ]->setFillColor( sf::Color( 0x11, 0x11, 0x11, alphas[ alphas.size() -1 ] ) );
		drops[ drops.size()-1 ]->setScale( 1, rand()%6 +1 );
	}
	
	reset();
}

void Rain::draw( sf::RenderWindow* &window )
{
	for( auto &it :drops )
	{
		window->draw( *it );
	}
}



void Rain::fadein( int v, int max )
{
	
}

void Rain::fadeout( int v, int min )
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



void Rain::mechanics()
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
