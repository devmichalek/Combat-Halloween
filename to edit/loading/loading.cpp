#include "loading.h"

Loading::Loading()
{
	state = 0;
}

Loading::~Loading()
{
	text.free();
	
	background.free();
	white_bar.free();
	green_bar.free();
}
	
void Loading::load( int screen_w, int screen_h )
{
	text.setID( "loading-text" );
	text.setFont( "intro/Jaapokki-Regular.otf", 40, 0xFF, 0xFF, 0xFF );
	text.setText( "Loading" );
	text.setAlpha( 255 );
	text.setPosition( screen_w/2 - text.getWidth()/2, screen_h/2 - text.getHeight()/2 );

	
	background.setName( "loading-background" );
	background.create( screen_w, screen_h, sf::Color( 0x15, 0x15, 0x1D ) );
	background.setAlpha( 255 );
	

	white_bar.setName( "loading-white_bar" );
	white_bar.create( 300, 50, sf::Color( 0xFF, 0xFF, 0xFF ) );
	white_bar.setAlpha( 255 );
	white_bar.setPosition( screen_w/2 - white_bar.getWidth()/2, text.getBot() +15 );


	green_bar.setName( "loading-green_bar" );
	green_bar.create( 1, 50, sf::Color( 0x70, 0xB7, 0x59 ) );
	green_bar.setAlpha( 255 );
	green_bar.setPosition( screen_w/2 - white_bar.getWidth()/2, text.getBot() +15 );
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
