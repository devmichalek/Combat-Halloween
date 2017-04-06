#include "effect.h"
#include "file/file.h"

Effect::Effect()
{
	line = 0;
	active = -1;
	counter = 0;
	alpha_line = 0;
}

Effect::~Effect()
{
	free();
}

void Effect::free()
{
	line = 0;
	active = -1;
	counter = 0;
	alpha_line = 0;
	
	if( !sprites.empty() )
	{
		for( auto &i :sprites )
		{
			i->free();
		}
		
		sprites.clear();
	}
}

void Effect::reset()
{
	active = -1;
	line = 50;
	counter = 0;
	alpha_line = 100;
}



void Effect::load( int screen_w, int screen_h )
{
	free();
	
	for( int i = 0; i < nr; i++ )
	{
		sprites.push_back( new MySprite() );
		sprites[ i ]->setName( "effect-sprites[" + con::itos( i ) +"]" );
		sprites[ i ]->create( screen_w, screen_h );
	}
	
	sprites[ WATER ]->setColor( sf::Color( 0x3B, 0x9C, 0xFB ) );
	sprites[ BLOOD ]->setColor( sf::Color( 0xFF, 0x81, 0x70 ) );
	sprites[ FALL ]->setColor( sf::Color( 0, 0, 0 ) );
	sprites[ LIGHTNING ]->setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
	sprites[ CRUNCHER ]->setColor( sf::Color( 0xA6, 0xA8, 0xAB ) );
	sprites[ SAND ]->setColor( sf::Color( 0xBE, 0x7F, 0x19 ) );
	sprites[ ACID ]->setColor( sf::Color( 0xA2, 0xF1, 0x49 ) );
	
	reset();
}

void Effect::draw( sf::RenderWindow* &window )
{
	if( active != -1 )
	{
		window->draw( sprites[ active ]->get() );
	}
}

void Effect::mechanics()
{
	if( active != -1 )
	{
		if( counter == 0 )
		{
			sprites[ active ]->fadeout( 2 );
			if( sprites[ active ]->getAlpha() == 0 )
			{
				active = -1;
			}
		}
		
		if( counter == 1 )
		{
			sprites[ active ]->fadein( 2, alpha_line );
			if( sprites[ active ]->getAlpha() == alpha_line )
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



void Effect::fadein( int v, int max )
{
	// empty
}

void Effect::fadeout( int v, int min )
{
	for( auto &i :sprites )
	{
		i->fadeout( v, min );
	}
}



void Effect::runWater()
{
	counter = 1;
	active = WATER;
}

void Effect::runBlood()
{
	counter = 1;
	active = BLOOD;
}

void Effect::runFall()
{
	counter = 1;
	active = FALL;
}

void Effect::runLightning()
{
	counter = 1;
	active = LIGHTNING;
}

void Effect::runSand()
{
	counter = 1;
	active = SAND;
}

void Effect::runAcid()
{
	counter = 1;
	active = ACID;
}

void Effect::runCruncher()
{
	counter = 1;
	active = CRUNCHER;
}