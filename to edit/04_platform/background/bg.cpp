#include "bg.h"

Bg::Bg()
{
	active = -1;
	line = 0;
	counter = 0;
	alpha_line = 0;
}

Bg::~Bg()
{
	free();
}

void Bg::free()
{
	if( !sprite.empty() )
	{
		for( auto &i :sprite )
		{
			i->free();
		}
		
		sprite.clear();
	}
	
	active = -1;
	line = 0;
	counter = 0;
	alpha_line = 0;
}

void Bg::reset()
{
	active = -1;
	line = 20;
	counter = 0;
	alpha_line = 100;
}


void Bg::load( int screen_w, int screen_h )
{
	for( int i = 0; i < nr; i++ )
	{
		sprite.push_back( new MySprite() );
		sprite[ i ]->setName( "bg-sprite[" + to_string(i) +"]" );
		sprite[ i ]->create( screen_w, screen_h );
	}
	
	sprite[ WATER ]->setColor( sf::Color( 0x3B, 0x9C, 0xFB ) );
	sprite[ BLOOD ]->setColor( sf::Color( 0xFF, 0x81, 0x70 ) );
	sprite[ FALL ]->setColor( sf::Color( 0, 0, 0 ) );
	
	active = -1;
	line = 50;
	counter = 0;
	alpha_line = 100;
}

void Bg::draw( sf::RenderWindow* &window )
{
	if( active != -1 )
	{
		window->draw( sprite[ active ]->get() );
		
		if( counter == 0 )
		{
			sprite[ active ]->fadeout( 2 );
			if( sprite[ active ]->getAlpha() == 0 )
			{
				active = -1;
			}
		}
		
		if( counter == 1 )
		{
			sprite[ active ]->fadein( 2, alpha_line );
			if( sprite[ active ]->getAlpha() == alpha_line )
			{
				counter = 2;
			}
		}
	}
	
	if( counter == line )
	{
		counter = 0;
	}
	else if( counter > 1 )
	{
		counter ++;
	}
}


void Bg::fadein( int v, int max )
{
	// empty
}

void Bg::fadeout( int v, int min )
{
	for( auto &i :sprite )
	{
		i->fadeout( v, min );
	}
}



void Bg::runWater()
{
	counter = 1;
	active = WATER;
}

void Bg::runBlood()
{
	counter = 1;
	active = BLOOD;
}

void Bg::runFall()
{
	counter = 1;
	active = FALL;
}
