#include "loading.h"

Loading::Loading()
{
	state = 0;
}

Loading::~Loading()
{
	background.free();
	green_bar.free();
	white_bar.free();
	text.free();
}
	
bool Loading::load( int screen_w, int screen_h )
{
	bool success = true;
	
	if( !text.setFont( "intro/Jaapokki-Regular.otf", 40, 0xFF, 0xFF, 0xFF ) )
		success = false;
	else if( !text.setText( "Loading" ) )
		success = false;
	else
	{
		text.setPosition( screen_w/2 - text.getWidth()/2, screen_h/2 - text.getHeight()/2 );
	}
		
	if( !background.create( screen_w, screen_h ) )
		success = false;
	else
	{
		background.setColor( 0x15, 0x15, 0x1D );
	}
	
	if( !green_bar.create( 1, 50 ) )
		success = false;
	else
	{
		green_bar.setColor( 0x70, 0xB7, 0x59 );
		text.setPosition( screen_w/2 - green_bar.getWidth()/2, text.getBot() +10 );
	}
	
	if( !white_bar.create( 300, 50 ) )
		success = false;
	else
	{
		white_bar.setColor( 0xFF, 0xFF, 0xFF );
		text.setPosition( screen_w/2 - white_bar.getWidth()/2, text.getBot() +10 );
	}
		
	return success;
}

void Loading::draw( sf::RenderWindow* &window )
{
	//green_bar.setScale( state );
	window->draw( background.get() );
	window->draw( white_bar.get() );
	window->draw( green_bar.get() );
	window->draw( text.get() );
	state ++;
}

int Loading::getState()
{
	return state;
}
