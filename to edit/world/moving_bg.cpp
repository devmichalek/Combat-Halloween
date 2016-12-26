#include "world/moving_bg.h"

Moving_bg::Moving_bg()
{
	screen_w = 0;
	screen_h = 0;
	
	vel = 0;
	x = y = 0;
}

Moving_bg::~Moving_bg()
{
	free();
}

void Moving_bg::free()
{
	sprite.free();
	
	screen_w = 0;
	screen_h = 0;
	
	vel = 0;
	x = y = 0;
}
	
	
	
void Moving_bg::load( string path, int w, int h )
{
	screen_w = w;
	screen_h = h;
	
	printf( "%d %d\n", screen_w, screen_h );
	
	sprite.setName( "moving_bg-sprite" );
	sprite.load( path );
	
	x = -(sprite.getWidth() -screen_w)*(0 *100 /screen_w) /100;
	y = -(sprite.getHeight() -screen_h)*((screen_h-238) *100 /screen_h) /100;
	
	sprite.setPosition( x, y );
	
	vel = 0.1;
}

void Moving_bg::draw( sf::RenderWindow* &window )
{
	window->draw( sprite.get() );
}

void Moving_bg::setXY( int posX, int posY )
{
	int new_x = -(sprite.getWidth() -screen_w)*(posX *100 /screen_w) /100;
	int new_y = -(sprite.getHeight() -screen_h)*(posY *100 /screen_h) /100;
	
	if( x != new_x )
	{
		if( x < new_x )	x += vel;
		else			x -= vel;
	}
	
	if( y != new_y )
	{
		if( y < new_y )	y += vel;
		else			y -= vel;
	}
	
	sprite.setPosition( x, y );
}
	
	
	
void Moving_bg::fadein( int v, int max )
{
	sprite.fadein( v, max );
}

void Moving_bg::fadeout( int v, int min )
{
	sprite.fadeout( v, min );
}