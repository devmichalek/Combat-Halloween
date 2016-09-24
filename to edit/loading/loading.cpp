#include "loading.h"

Loading::Loading()
{
	state = 0;
	counter = 0;
}

Loading::~Loading()
{
	text.free();
	background.free();
	
	progress_bar.free();
	counter = 0;
}
	
void Loading::load( int screen_w, int screen_h )
{
	text.setID( "loading-text" );
	text.setFont( "intro/Jaapokki-Regular.otf", 40, 0xFF, 0xFF, 0xFF );
	text.setText(  "Loading " + to_string( state ) + "%"  );
	text.setAlpha( 255 );
	text.center( screen_w, screen_h );

	
	background.setName( "loading-background" );
	background.create( screen_w, screen_h );
	background.setColor( sf::Color( 0x15, 0x15, 0x1D ) );
	background.setAlpha( 255 );
	

	progress_bar.setName( "loading-progress_bar" );
	progress_bar.load( "loading/progress bar.png", 8 );
	progress_bar.setAlpha( 255 );
	progress_bar.setPosition( screen_w/2 - progress_bar.getWidth()/2, text.getBot() +15 );
}

void Loading::draw( sf::RenderWindow* &window, int range )
{
	window->draw( background.get() );
	
	window->draw( text.get() );
	text.setText( "Loading " + to_string( state ) + "%" );
	text.reloadPosition();
	
	state ++;
	
	progress_bar.setOffset( counter /5 );
	window->draw( progress_bar.get() );
	
	counter++;
	if( counter == 8 *5 )
	{
		counter = 0;
	}
}

int Loading::getState()
{
	return state;
}
