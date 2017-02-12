#include "background.h"

Background::Background()
{
	screen_w = 0;
	screen_h = 0;
}

Background::~Background()
{
	free();
}

void Background::free()
{
	screen_w = 0;
	screen_h = 0;
	
	sprite.free();
}

void Background::reset( int x, int y )
{
	setPosition( x, y );
}



void Background::load( int type, int screen_w, int screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	sprite.setName( "background-sprite" );
	sprite.load( "data/sprites/play/" +to_string( type ) +".png" );
	
}

void Background::draw( sf::RenderWindow* &window )
{
	window->draw( sprite.get() );
}


void Background::fadein( int v, int max )
{
	sprite.fadein( v, max );
}

void Background::fadeout( int v, int min )
{
	sprite.fadeout( v, min );
}



void Background::setPosition( int x, int y )
{
	float new_x = -( screen_w/2 ) *x /screen_w;
	float new_y = -150 *( y +300 ) /screen_h;
	
	if( new_y > -( sprite.getHeight() -screen_h ) && new_y < 0 )
	{
		sprite.setPosition( new_x, new_y );
	}
}

sf::Uint8 Background::getAlpha()
{
	return sprite.getAlpha();
}

void Background::setColor( sf::Color color )
{
	sprite.setColor( color );
}