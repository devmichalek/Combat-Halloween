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
	
	text.setFont( "intro/Jaapokki-Regular.otf", 40, 0xFF, 0xFF, 0xFF );

	text.setText( "Loading" );


	text.setAlpha( 255 );
	text.setPosition( screen_w/2 - text.getWidth()/2, screen_h/2 - text.getHeight()/2 );

	
	
	background.setAlpha( 255 );
	background.create( screen_w, screen_h, 0x15, 0x15, 0x1D );
	
	
	white_bar.setAlpha( 255 );
	white_bar.create( 300, 50, 0xFF, 0xFF, 0xFF );
	white_bar.setPosition( screen_w/2 - white_bar.getWidth()/2, text.getBot() +15 );

	
	green_bar.setAlpha( 255 );
	green_bar.create( 1, 50, 0x70, 0xB7, 0x59 );
	green_bar.setPosition( screen_w/2 - white_bar.getWidth()/2, text.getBot() +15 );
	
		
	return success;
}

void Loading::draw( sf::RenderWindow* &window, int range )
{
	green_bar.setScale( white_bar.getWidth() *state/range );
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
