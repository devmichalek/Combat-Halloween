#include "loading_world.h"
#include "own/file.h"

Loading_world::Loading_world()
{
	free();
}

Loading_world::~Loading_world()
{
	free();
}

void Loading_world::free()
{
	screen_w = 0;
	screen_h = 0;
	ready = false;
	stop = false;
	
	state = 0;
	info.free();
	
	counter = 0;
	max = 0;
	progress_bar.free();
}
	
void Loading_world::load( float screen_w, float screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	// Set info.
	info.setIdentity( "loading_world-info" );
	info.setFont( "fonts/Jaapokki-Regular.otf" );
	info.setSize( screen_h /24 );
	info.setAlpha( 0xFF );
	info.setText( "Downloading data..." );
	info.setPosition( screen_w/2 -info.getWidth()/2 +screen_w/160, screen_h/2 -info.getHeight()/2 -screen_h/72 );
	
	// Set progress bar.
	max = 20;
	progress_bar.setIdentity( "loading_world-progress_bar" );
	progress_bar.load( "images/initialization/progress_bar.png", static_cast <int> (max) );
	progress_bar.setScale( screen_w /1707, screen_h /960 );
	progress_bar.setAlpha( 0xFF );
	progress_bar.setPosition( screen_w/2 - progress_bar.getWidth()/2, screen_h/2 +screen_h/36 );
	setSuccess();
}

void Loading_world::draw( sf::RenderWindow* &window, double elapsedTime )
{
	window->draw( info.get() );
	
	if( !ready )
	{
		if( !stop )
		{
			progress_bar.setOffset( static_cast <int> (counter) );
		}
	}
	
	window->draw( progress_bar.get() );
	
	counter += elapsedTime *0xFF /8;
	if( counter >= max )
	{
		counter = 0;
	}
	
	if( ready )
	{
		info.fadeout( elapsedTime *0xFF *2 );
		progress_bar.fadeout( elapsedTime *0xFF *2 );
	}
}



const sf::Uint8& Loading_world::getState()
{
	state ++;
	return state;
}

bool Loading_world::isReady()
{
	if( ready && progress_bar.getAlpha() == 0 )
	{
		return true;
	}
	
	return false;
}

void Loading_world::unStop()
{
	state = 0;
	stop = false;
}

bool Loading_world::getStop()
{
	return stop;
}



void Loading_world::setError()
{
	info.setText( "We've got an error..." );
	info.setColor( sf::Color( 0xF2, 0x58, 0x3E ) );
	info.setPosition( screen_w/2 -info.getWidth()/2 +screen_w/160, screen_h/2 -info.getHeight()/2 -screen_h/72 );
	stop = true;
}

void Loading_world::setSuccess()
{
	info.setText( "Rightly loaded data!" );
	info.setColor( sf::Color( 0x58, 0x70, 0x58 ) );
	info.setPosition( screen_w/2 -info.getWidth()/2 +screen_w/160, screen_h/2 -info.getHeight()/2 -screen_h/72 );
	stop = true;
	ready = true;
}