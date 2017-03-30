#include "04_platform/panel/scores/scores.h"
#include "file/file.h"

Scores::Scores()
{
	free();
}

Scores::~Scores()
{
	free();
}

void Scores::free()
{
	text.free();
	
	result = 0;
	last_result = 0;
	screen_w = 0;
	
	scale = 0;
	scale_bot = 0;
	scale_top = 0;
	scale_vel = 0;
}

void Scores::reset()
{
	result = 0;
	last_result = 0;
	scale = scale_bot;
	
	text.setText( con::itos( result ) );
	text.setScale( scale, scale );
	text.setPosition( screen_w /2 -text.getWidth() /2, 5 );
}



void Scores::load( int screen_w )
{
	free();
	
	this->screen_w = screen_w;
	
	text.setName( "scores-text" );
	text.setFont( "data/00_loading/Jaapokki-Regular.otf", 42, 0xD9, 0xD9, 0xD9 );
	text.setText( "0" );
	text.setPosition( screen_w /2 -text.getWidth() /2, 5 );
	
	scale_bot = 1;
	scale_top = 1.85;
	scale_vel = 0.05;
	scale = scale_bot;
}

void Scores::draw( sf::RenderWindow* &window )
{
	window->draw( text.get() );
}

void Scores::mechanics()
{
	if( result != last_result )
	{
		last_result = result;
		text.setText( con::itos( result ) );
		text.reloadPosition();
	}
	
	if( scale > scale_bot )
	{
		scale -= scale_vel;
		text.setScale( scale, scale );
		text.setPosition( screen_w /2 -text.getWidth() /2, 5 );
	}
}



void Scores::fadein( int v, int max )
{
	text.fadein( v, max *0.6 );
}

void Scores::fadeout( int v, int min )
{
	text.fadeout( v, min );
}



void Scores::add( int amount )
{
	result += amount;
	scale = scale_top;
}