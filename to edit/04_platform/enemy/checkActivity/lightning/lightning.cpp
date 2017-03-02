#include "04_platform/enemy/checkActivity/lightning/lightning.h"

Lightning::Lightning()
{
	delay = 0;
	line = 0;
	counter_line = 0;
	fps = 0;
	addCounter_line = 0;
	reset();
}

Lightning::~Lightning()
{
	free();
}

void Lightning::free()
{
	sprite.free();
	
	delay = 0;
	counter_line = 0;
	fps = 0;
	reset();
}

void Lightning::reset()
{
	offset = 0;
	state = 0;
	counter = 0;
	counter_line = 20 *fps;
	addCounter_line = 0.75 *fps;
	addCounter = 0;
}



void Lightning::load( int fps )
{
	line = 8;
	sprite.setName( "lightning-sprite" );
	sprite.load( "data/04_platform/enemy/lightning/0.png", line );
	
	delay = 10;
	this->fps = fps;
	reset();
}

void Lightning::draw( sf::RenderWindow* &window )
{
	if( state > 0 )
	{
		sprite.setOffset( offset /delay );
		window->draw( sprite.get() );
	}
}

void Lightning::fadein( int v, int max )
{
	sprite.fadein( v, max /2 );
}

void Lightning::fadeout( int v, int min )
{
	sprite.fadeout( v, min );
}



void Lightning::moveX( sf::Uint8 direction, float vel )
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

void Lightning::undoFall( sf::Uint8 add )
{
	sprite.setPosition( sprite.getX() +add, sprite.getY() );
}

void Lightning::mechanics( Rect* rect, sf::Uint8 direction )
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
			if( rect != NULL )
			{
				int bot = rect->getY() +rect->getHeight();
				int x = rect->getX() +rect->getWidth()/2;
				
				sprite.setPosition( x -sprite.getWidth() *0.38, bot -sprite.getHeight() );
			}
			counter = 0;
			state = 1;
		}
	}
	else if( state > 0 )
	{
		if( state == 1 )
		{
			addCounter ++;
			if( addCounter >= addCounter_line )
			{
				state = 2;
				addCounter = 0;
			}
		}
		else if( state == 2 )
		{
			offset ++;
			if( offset == line *delay )
			{
				offset = 0;
				state = 0;
			}
		}
	}
}

bool Lightning::harmSomebody( Rect* rect )
{
	if( rect != NULL && state == 2 )
	{
		int h = 20;
		int w = sprite.getWidth() /2;
		if( rect->checkCollision( sprite.getX() +w/2, sprite.getY() +sprite.getHeight() -h, w, h ) )
		{
			return true;
		}
	}
	
	return false;
}

int Lightning::getDamage()
{
	return 0xFF;
}

bool Lightning::harmed()
{
	if( offset == 5 *delay )
	{
		return true;
	}
	
	return false;
}