#include "loading.h"
#include "own/file.h"

Loading::Loading()
{
	free();
}

Loading::~Loading()
{
	free();
}

void Loading::free()
{
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
}

void Loading::draw( sf::RenderWindow* &window, double elapsedTime )
{
	window->draw( text.get() );
	
	if( !ready )
	{
		setText();
		state ++;
		progress_bar.setOffset( static_cast <int> (counter) );
	}
	
	window->draw( progress_bar.get() );
	
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
}