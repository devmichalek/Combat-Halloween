#include "eye.h"
#include <cstdlib>

Eye::Eye()
{
	free();
}

Eye::~Eye()
{
	free();
}

void Eye::free()
{
	screen_w = 0;
	screen_h = 0;
	
	line_y = 0;
	distance_y = 0;
	
	x = y = 0;
	scale_x = 0;
	
	sprite.free();
	
	balloonchat.free();
	if( !texts.empty() )
	{
		texts.clear();
	}
	textWas = -1;
	textCounter = 0;
	textLine = 6;
}

void Eye::reset( float x, float y )
{
	distance_y = 0;
	
	this->x = x;
	this->y = y;
	scale_x = 0;
	sprite.setPosition( x, y );
	
	// Texts.
	textWas = -1;
	textCounter = 0;
}



void Eye::load( float screen_w, float screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	sprite.setIdentity( "eye-sprite" );
	sprite.load( "images/play/knight/eye.png" );
	sprite.setScale( 0.5, 0.5 );
	line_y = sprite.getHeight() /3 *2;
	scale_x = 0.5;

	// Set texts.
	balloonchat.load( screen_w, screen_h );
	
	srand( time( NULL ) );
}

void Eye::draw( sf::RenderWindow* &window )
{
	if( scale_x < 0 )
	{
		float x = sprite.getX();
		sprite.setPosition( sprite.getX() +sprite.getWidth(), sprite.getY() );
		window->draw( sprite.get() );
		sprite.setPosition( x, sprite.getY() );
	}
	else
	{
		window->draw( sprite.get() );
	}
	
	// Draw texts.
	if( textCounter > 0 )
	{
		bool left = false;
		if( scale_x > 0 )	left = false;
		else				left = true;
		balloonchat.setPosition( sprite.getX() +sprite.getWidth()/2, sprite.getY(), !left );
		balloonchat.draw( window );
	}
}

void Eye::mechanics( double elapsedTime )
{
	if( textCounter > 0 && textCounter < textLine )
	{
		textCounter += elapsedTime;
		if( textCounter > textLine )
		{
			textCounter = 0;
		}
	}
	
	
	// Hovering.
	distance_y -= elapsedTime *4;
	if( distance_y < -line_y )
	{
		distance_y = 0;
	}
	
	// Set eye.
	if( sprite.getX() < x -sprite.getWidth()/2 )
	{
		sprite.move( elapsedTime *((x-sprite.getWidth()/2) -sprite.getX()) *2, 0 );
		sprite.setScale( -0.5, 0.5 );
		scale_x = -0.5;
	}
	else if( sprite.getX() > x -sprite.getWidth()/2 )
	{
		sprite.move( -elapsedTime *(sprite.getX() -(x-sprite.getWidth()/2)) *2, 0 );
		sprite.setScale( 0.5, 0.5 );
		scale_x = 0.5;
	}

	
	if( sprite.getY() < y +distance_y )
	{
		sprite.move( 0, elapsedTime *((y+distance_y) -sprite.getY()) *2 );
	}
	else if( sprite.getY() > y +distance_y )
	{
		sprite.move( 0, -elapsedTime *(sprite.getY() -(y+distance_y)) *2 );
	}
}



void Eye::fadein( float v, int max )
{
	sprite.fadein( v, max );
	balloonchat.fadein( v, max );
}

void Eye::fadeout( float v, int min )
{
	sprite.fadeout( v, min );
	balloonchat.fadeout( v, min );
}



void Eye::setPosition( float x, float y )
{
	this->x = x;
	this->y = y;
}