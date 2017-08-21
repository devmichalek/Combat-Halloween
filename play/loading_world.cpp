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
	resetbutton.free();
	
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
	unStop();
	
	// Set progress bar.
	max = 20;
	progress_bar.setIdentity( "loading_world-progress_bar" );
	progress_bar.load( "images/initialization/progress_bar.png", static_cast <int> (max) );
	progress_bar.setScale( screen_w /1707, screen_h /960 );
	progress_bar.setAlpha( 0xFF );
	progress_bar.setPosition( screen_w/2 - progress_bar.getWidth()/2, screen_h/2 +screen_h/36 );
	
	resetbutton.setIdentity( "login-loginbutton" );
	resetbutton.setFont( "fonts/Jaapokki-Regular.otf" );
	int size = screen_h /28;
	resetbutton.create( "RELOAD", size, size /30 +2 );
	resetbutton.setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
	resetbutton.setColorText( sf::Color( 0x21, 0x21, 0x29 ) );
	resetbutton.setPosition( screen_w/2 -resetbutton.getWidth()/2, progress_bar.getBot() +screen_h/72 );
	resetbutton.fadeinGlobal( 0xFF );
}

void Loading_world::handle( sf::Event& event )
{
	if( stop && !ready )
	{
		resetbutton.handle( event );
	}
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
		else if( resetbutton.getClicked() )
		{
			resetbutton.getClicked() = false;
			resetbutton.getFocus() = false;
			unStop();
		}
	}
	
	window->draw( progress_bar.get() );
	
	if( stop && !ready )
	{
		resetbutton.draw( window, elapsedTime );
	}
	
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
	if( state < 0xFF )
	{
		state ++;
	}
	
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
	
	info.setText( "Downloading data..." );
	info.setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
	info.setPosition( screen_w/2 -info.getWidth()/2, screen_h/2 -info.getHeight()/2 -screen_h/72 );
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