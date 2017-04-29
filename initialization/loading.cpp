/**
    loading.h
    Purpose: class Loading - to show progress during loading objects.

    @author Adrian Michalek
    @version 2016.10.05
	@email adrmic98@gmail.com
*/

#include "loading.h"
#include "file/file.h"

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
	
	progress_bar.free();
	counter = 0;
	max = 0;
	state = 0;
}
	
void Loading::load( unsigned screen_w, unsigned screen_h )
{
	free();
	max = 20;
	
	text.setName( "loading-text" );
	text.setFont( "data/initialization/Jaapokki-Regular.otf", 40, 255, 255, 255 );
	text.setText( ("Loading " + con::itos( state ) + "%")  );
	text.setAlpha( 0xFF );
	
	progress_bar.setName( "loading-progress_bar" );
	progress_bar.load( "data/initialization/progress_bar.png", max );
	progress_bar.setAlpha( 0xFF );
	
	text.setPosition( screen_w/2 -text.getWidth()/2, screen_h/2 -text.getHeight()/2 -10 );
	progress_bar.setPosition( screen_w/2 - progress_bar.getWidth()/2, screen_h/2 +20 );
}

void Loading::draw( sf::RenderWindow* &window )
{
	window->draw( text.get() );
	text.setText( "Loading " + con::itos( state ) + "%" );
	text.reloadPosition();
	
	state ++;
	
	progress_bar.setOffset( counter/6 );
	window->draw( progress_bar.get() );
	
	counter++;
	if( counter == max *6 )
	{
		counter = 0;
	}
}

const sf::Uint8& Loading::getState() const
{
	return state;
}