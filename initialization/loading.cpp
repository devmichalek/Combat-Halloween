#include "loading.h"
#include "own/file.h"

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
	w = h = 0;
	text.free();
	
	progress_bar.free();
	counter = 0;
	max = 0;
	state = 0;
}
	
void Loading::load( unsigned screen_w, unsigned screen_h )
{
	free();
	
	w = screen_w;
	h = screen_h;
	max = 20;
	text.setIdentity( "loading-text" );
	text.setFont( "fonts/Jaapokki-Regular.otf" );
	text.setText( ("Loading " + con::itos( state ) + "%")  );
	text.setSize( screen_h /16 );
	text.setAlpha( 0xFF );
	
	progress_bar.setIdentity( "loading-progress_bar" );
	progress_bar.load( "images/initialization/progress_bar.png", max );
	progress_bar.setScale( static_cast <float> (screen_h) /960, static_cast <float> (screen_h) /960 );
	progress_bar.setAlpha( 0xFF );
	
	text.setPosition( w/2 -text.getWidth()/2 +w/160, h/2 -text.getHeight()/2 -h/72 );
	progress_bar.setPosition( screen_w/2 - progress_bar.getWidth()/2, screen_h/2 +screen_h/36 );
}

void Loading::draw( sf::RenderWindow* &window, double elapsedTime )
{
	window->draw( text.get() );
	
	if( !ready )
	{
		text.setText( "Loading " + con::itos( state ) + "%" );
		text.setPosition( w/2 -text.getWidth()/2 +w/160, h/2 -text.getHeight()/2 -h/72 );
		
		state ++;
		
		progress_bar.setOffset( counter/3 );
	}
	
	window->draw( progress_bar.get() );
	
	counter++;
	if( counter == max *3 )
	{
		counter = 0;
	}
	
	if( ready )
	{
		text.fadeout( elapsedTime *128 );
		progress_bar.fadeout( elapsedTime *128 );
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