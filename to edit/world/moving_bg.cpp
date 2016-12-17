#include "world/moving_bg.h"

Moving_bg::Moving_bg()
{
	vel = 0;
	direction = 0;
	x1 = x2 = 0;
}

Moving_bg::~Moving_bg()
{
	free();
}

void Moving_bg::free()
{
	one.free();
	two.free();
	
	vel = 0;
	direction = 0; // none
	x1 = x2 = 0;
}
	
void Moving_bg::load( string path )
{
	one.setName( "moving_bg-one" );
	one.load( path );
	one.setPosition( -one.getWidth()/2, 0 );
	x1 = -one.getWidth()/2;
	
	two.setName( "moving_bg-two" );
	two.load( path );
	two.setPosition( two.getWidth()/2, 0 );
	x2 = two.getWidth()/2;
	
	vel = 0.10;
}

void Moving_bg::draw( sf::RenderWindow* &window )
{
	window->draw( one.get() );
	window->draw( two.get() );
	
	if( direction == 1 ) // left
	{
		if( one.getRight() >= one.getWidth()*2 )
		{
			one.setPosition( two.getLeft() -one.getWidth(), 0 );
			x1 = two.getLeft();
		}
		
		if( two.getRight() >= two.getWidth()*2 )
		{
			two.setPosition( one.getLeft() -two.getWidth(), 0 );
			x2 = one.getLeft();
		}
		
		x1 += vel;
		x2 += vel;
		
		one.setPosition( x1, 0 );
		two.setPosition( x2, 0 );
	}
	
	else if( direction == 2 ) // right
	{
		if( one.getX() <= -one.getWidth() )
		{
			one.setPosition( two.getRight(), 0 );
			x1 = two.getRight();
		}
		
		if( two.getX() <= -two.getWidth() )
		{
			two.setPosition( one.getRight(), 0 );
			x2 = one.getRight();
		}
		
		x1 -= vel;
		x2 -= vel;
		
		one.setPosition( x1, 0 );
		two.setPosition( x2, 0 );
	}
	
	// printf( "1: %d, 2: %d\n", one.getX(), two.getX() );
}

void Moving_bg::move( sf::Uint8 direction )
{
	this->direction = direction;
}
	
void Moving_bg::fadein( int v, int max )
{
	one.fadein( v, max );
	two.fadein( v, max );
}

void Moving_bg::fadeout( int v, int min )
{
	one.fadeout( v, min );
	two.fadeout( v, min );
}