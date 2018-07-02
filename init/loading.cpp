<<<<<<< HEAD
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
=======
#include "loading.h"
#include "own/file.h"

Loading::Loading()
{
	free();
>>>>>>> Combat-Halloween/master
}

Loading::~Loading()
{
	free();
}

void Loading::free()
{
<<<<<<< HEAD
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
	text.setFont( "data/initialization/Jaapokki-Regular.otf", 45, 255, 255, 255 );
	text.setText( ("Loading " + con::itos( state ) + "%")  );
	text.setAlpha( 0xFF );
	
	progress_bar.setName( "loading-progress_bar" );
	progress_bar.load( "data/initialization/progress_bar.png", max );
	progress_bar.setAlpha( 0xFF );
	
	text.setPosition( screen_w/2 -text.getWidth()/2 +8, screen_h/2 -text.getHeight()/2 -10 );
	progress_bar.setPosition( screen_w/2 - progress_bar.getWidth()/2, screen_h/2 +20 );
=======
	screen_w = 0;
	screen_h = 0;
	ready = false;
	
	text.free();
	state = 0;
	
	counter = 0;
	max = 0;
	progress_bar.free();
}
	
void Loading::load( float screen_w, float screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	// Set text.
	text.setIdentity( "loading-text" );
	text.setFont( "fonts/Jaapokki-Regular.otf" );
	text.setSize( screen_h /24 );
	text.setAlpha( 0xFF );
	
	// Set progress bar.
	max = 20;
	progress_bar.setIdentity( "loading-progress_bar" );
	progress_bar.load( "images/initialization/progress_bar.png", static_cast <int> (max) );
	progress_bar.setScale( screen_w /1707, screen_h /960 );
	progress_bar.setAlpha( 0xFF );
	
	// The rest.
	setText();
	progress_bar.setPosition( screen_w/2 - progress_bar.getWidth()/2, screen_h/2 +screen_h/36 );
>>>>>>> Combat-Halloween/master
}

void Loading::draw( sf::RenderWindow* &window )
{
	window->draw( text.get() );
<<<<<<< HEAD
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
=======
	window->draw( progress_bar.get() );
}

void Loading::mechanics( double elapsedTime )
{
	counter += elapsedTime *0xFF /8;
	if( counter >= max )
	{
		counter = 0;
	}
	
	if( ready )
	{
		text.fadeout( elapsedTime *0xFF *2 );
		progress_bar.fadeout( elapsedTime *0xFF *2 );
	}
	else
	{
		setText();
		state ++;
		progress_bar.setOffset( static_cast <int> (counter) );
	}
}



const sf::Uint8& Loading::getState() const
{
	return state;
}

bool Loading::isReady()
{
	if( ready && progress_bar.getAlpha() == 0 )
	{
		return true;
	}
	
	return false;
}



void Loading::beReady()
{
	ready = true;
}

void Loading::setText()
{
	text.setText( ( "Loading " + con::itos( state ) + "%" )  );
	text.setPosition( screen_w/2 -text.getWidth()/2 +screen_w/160, screen_h/2 -text.getHeight()/2 -screen_h/72 );
>>>>>>> Combat-Halloween/master
}