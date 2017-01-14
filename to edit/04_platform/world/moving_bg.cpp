#include "moving_bg.h"

Moving_bg::Moving_bg()
{
	screen_w = 0;
	screen_h = 0;
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
}
	
	
	
void Moving_bg::load( string path, int w, int h )
{
	screen_w = w;
	screen_h = h;
	
	// printf( "%d %d\n", screen_w, screen_h );
	
	sprite.setName( "moving_bg-sprite" );
	sprite.load( path );
}

void Moving_bg::draw( sf::RenderWindow* &window )
{
	window->draw( sprite.get() );
}

void Moving_bg::setXY( int posX, int posY )
{
	float new_x = -500 *posX /screen_w;
	float new_y = -150 *(posY+300) /screen_h;
	
	if( new_y > -(sprite.getHeight() -screen_h) && new_y < 0 )
	{
		sprite.setPosition( new_x, new_y );
	}
}
	
	
	
void Moving_bg::fadein( int v, int max )
{
	sprite.fadein( v, max );
}

void Moving_bg::fadeout( int v, int min )
{
	sprite.fadeout( v, min );
}