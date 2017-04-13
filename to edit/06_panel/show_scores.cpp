#include "show_scores.h"
#include "file/file.h"

Show_scores::Show_scores()
{
	free();
}

Show_scores::~Show_scores()
{
	free();
}

void Show_scores::free()
{
	screen_w = 0;
	screen_h = 0;
	
	max = min = 0;
	n = 0;
	vel = 0;
	text.free();
	summary.free();
}

void Show_scores::reset()
{
	n = min;
	vel = 1;
	
	text.setText( con::itos( n ) );
	text.center( screen_w /2, screen_h/3 );
}


void Show_scores::load( int screen_w, int screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	text.setName( "show_scores-text" );
	text.setFont( "data/00_loading/Jaapokki-Regular.otf", 70, 0xFF, 0xFF, 0xFF );
	
	summary.setName( "show_scores-summary" );
	summary.setFont( "data/00_loading/Jaapokki-Regular.otf", 100, 0xFF, 0xFF, 0xFF );
	summary.setText( "Summary" );
	summary.center( screen_w, screen_h/3 );
	
	reset();
}

void Show_scores::draw( sf::RenderWindow* &window )
{
	window->draw( text.get() );
	
	if( text.getAlpha() == 0xFF )
	{
		mechanics();
	}
}

void Show_scores::mechanics()
{
	if( n < max )
	{
		n += vel;
		if( n > max )	n = max;
		text.setText( con::itos( n ) );
		text.center( screen_w /2, screen_h/3 );
	}
}

void Show_scores::set( int scores )
{
	n = 0;
	min = 0;
	max = scores;
	vel += scores /500;
	text.setText( "0" );
	text.center( screen_w /2, screen_h/3 );
}


void Show_scores::fadein( int v, int max )
{
	text.fadein( v, max );
}

void Show_scores::fadeout( int v, int min )
{
	text.fadeout( v, min );
}
