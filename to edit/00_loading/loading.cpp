/**
    loading.h
    Purpose: class Loading - to show progress during loading objects.

    @author Adrian Michalek
    @version 2016.10.05
	@email adrmic98@gmail.com
*/

#include "loading.h"

Loading::Loading()
{
	state = 0;
	counter = 0;
	max = 0;
}

Loading::~Loading()
{
	free();
}

void Loading::free()
{
	text.free();
	bg.free();
	
	progress_bar.free();
	counter = 0;
	max = 0;
	state = 0;
}
	
void Loading::load( unsigned screen_w, unsigned screen_h )
{
	free();
	max = 8;
	
	text.setName( "loading-text" );
	text.setFont( "data/fonts/Jaapokki-Regular.otf", 40, 255, 255, 255 );
	text.setText( "Loading " + to_string( state ) + "%"  );
	text.setAlpha( 0xFF );
	text.center( screen_w, screen_h );

	
	progress_bar.setName( "loading-progress_bar" );
	progress_bar.load( "data/sprites/loading/progress_bar.png", max );
	progress_bar.setAlpha( 0xFF );
	progress_bar.setPosition( screen_w/2 - progress_bar.getWidth()/2, text.getBot() +15 );
	
	
	bg.setName( "loading-background" );
	bg.create( screen_w, screen_h ); 
	bg.setColor( sf::Color( 21, 21, 29 ) );
	bg.setAlpha( 0xFF );
}

void Loading::draw( sf::RenderWindow* &window )
{
	window->draw( bg.get() );
	
	window->draw( text.get() );
	text.setText( "Loading " + to_string( state ) + "%" );
	text.reloadPosition();
	
	state ++;
	
	progress_bar.setOffset( counter /5 );
	window->draw( progress_bar.get() );
	
	counter++;
	if( counter == max *5 )
	{
		counter = 0;
	}
}

const sf::Uint8& Loading::getState() const
{
	return state;
}
