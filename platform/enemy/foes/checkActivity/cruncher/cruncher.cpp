#include "cruncher.h"

Cruncher::Cruncher()
{
	delay = 0;
	line = 0;
	
	counter_line = 0;
	
	fps = 0;
	screen_w = 0;
	
	reset();
}

Cruncher::~Cruncher()
{
	free();
}

void Cruncher::free()
{
	sprite.free();
	
	fps = 0;
	delay = 0;
	counter_line = 0;
	
	reset();
}

void Cruncher::reset()
{
	offset = 0;
	state = 0;
	counter = 0;
	counter_line = 20 *fps;
}



void Cruncher::load( int fps, int screen_w )
{
	free();
	
	this->fps = fps;
	this->screen_w = screen_w;
	
	line = 6;
	delay = 12;
	
	sprite.setName( "cruncher-sprite" );
	sprite.load( "data/04_platform/enemy/checkActivity/cruncher/0.png", line );
	sprite.setScale( 0.5, 0.5 );
	
	reset();
}

void Cruncher::draw( sf::RenderWindow* &window )
{
	if( state > 0 )
	{
		sprite.setOffset( offset /delay );
		window->draw( sprite.get() );
	}
}

void Cruncher::fadein( int v, int max )
{
	sprite.fadein( v, max );
}

void Cruncher::fadeout( int v, int min )
{
	sprite.fadeout( v, min );
}



void Cruncher::moveX( sf::Uint8 direction, float vel )
{
	if( state > 0 )
	{
		if( direction == 1 )
		{
			sprite.setPosition( sprite.getX() +vel, sprite.getY() );
		}
		else if( direction == 2 )
		{
			sprite.setPosition( sprite.getX() -vel, sprite.getY() );
		}
	}
}

void Cruncher::undoFall( sf::Uint8 add )
{
	sprite.setPosition( sprite.getX() +add, sprite.getY() );
}

void Cruncher::mechanics( int y, sf::Uint8 direction )
{
	if( direction != 0 )
	{
		counter = 0;
	}
	
	if( state == 0 )
	{
		counter ++;
		if( counter >= counter_line )
		{
			sprite.setPosition( screen_w, y -sprite.getHeight()/2 );
			
			counter = 0;
			state = 1;
			offset = 0;
		}
	}
	
	else if( state > 0 )
	{
		offset ++;
		if( offset == line *delay )
		{
			offset = 0;
		}
		
		sprite.setPosition( sprite.getX() -2, sprite.getY() );
		
		if( sprite.getX() +sprite.getWidth() < 0 )
		{
			state = 0;
			offset = 0;
		}
	}
}

bool Cruncher::harmSomebody( Rect* rect )
{
	if( rect != NULL && state > 0 )
	{
		if( rect->checkCollision( sprite.getX(), sprite.getY(), sprite.getWidth(), sprite.getHeight() ) )
		{
			state = 0;
			
			return true;
		}
	}
	
	return false;
}

int Cruncher::getDamage()
{
	return 0xFF;
}