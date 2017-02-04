#include "loading_world.h"

Loading_world::Loading_world()
{
	state = 0;
	ready = false;
	counter = 0;
	max = 0;
}

Loading_world::~Loading_world()
{
	free();
}

void Loading_world::free()
{
	text.free();
	bg.free();
	
	state = 0;
	ready = false;
	counter = 0;
	max = 0;
	progress_bar.free();
}

void Loading_world::reset()
{
	ready = false;
	setText( "" );
}



void Loading_world::load( unsigned screen_w, unsigned screen_h )
{
	free();
	max = 20;
	
	text.setName( "loading_world-text" );
	text.setFont( "data/fonts/Jaapokki-Regular.otf", 20, 0xFF, 0xFF, 0xFF );
	text.setText( " " );
	text.setPosition( 10, screen_h -35 );

	
	progress_bar.setName( "loading_world-progress_bar" );
	progress_bar.load( "data/sprites/loading_world/gears.png", max );
	progress_bar.setPosition( screen_w/2 -progress_bar.getWidth()/2, screen_h/2 -progress_bar.getHeight()/2 );
	
	
	bg.setName( "loading_world-background" );
	bg.create( screen_w, screen_h ); 
	bg.setColor( sf::Color( 21, 21, 29 ) );
}

void Loading_world::draw( sf::RenderWindow* &window )
{
	window->draw( bg.get() );
	
	window->draw( text.get() );

	
	progress_bar.setOffset( counter /4 );
	
	window->draw( progress_bar.get() );
	
	counter++;
	if( counter == max *4 )
	{
		counter = 0;
	}
	
	if( ready )
	{
		fadeout( 3 );
	}
	else
	{
		fadein( 3 );
	}
}



void Loading_world::fadein( int j, int max )
{
	text.fadein( j, max );
	bg.fadein( j, max );
	progress_bar.fadein( j, max );
}

void Loading_world::fadeout( int j, int min )
{
	text.fadeout( j, min );
	bg.fadeout( j, min );
	progress_bar.fadeout( j, min );
}



void Loading_world::setReady()
{
	ready = true;
}

void Loading_world::setText( string line )
{
	text.setText( line );
	text.reloadPosition();
}

bool Loading_world::nextState()
{
	if( ready && bg.getAlpha() == 0 )
	{
		return true;
	}
	
	return false;
}

int Loading_world::getState()
{
	return state;
}

void Loading_world::setState( int s )
{
	state = s;
}

bool Loading_world::readyToLoad()
{
	if( bg.getAlpha() == 0xFF )
	{
		return true;
	}
	
	return false;
}