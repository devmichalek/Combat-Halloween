#include "pausesystem.h"

Pausesystem::Pausesystem()
{
	free();
}

Pausesystem::~Pausesystem()
{
	free();
}

void Pausesystem::free()
{
	blackout.free();
	text.free();
	
	active = false;
	changed = false;
	release = false;
	
	click.free();
	playable = true;
}



void Pausesystem::load( float screen_w, float screen_h )
{
	free();
	
	blackout.setIdentity( "pausesystem-blackout" );
	blackout.create( screen_w, screen_h );
	blackout.setColor( sf::Color( 0, 0, 0, 0 ) );
	
	text.setIdentity( "pausesystem-text" );
	text.setFont( "fonts/jcandlestickextracond.ttf" );
	text.setText( "PAUSED" );
	text.setSize( screen_h /10 );
	text.setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
	text.center( 0, 0, screen_w, screen_h );
	
	click.setIdentity( "pausesystem-chunk" );
	click.load( "sounds/click.wav" );
}

void Pausesystem::handle( sf::Event& event )
{
	// keyboard stuff
	if( event.type == sf::Event::KeyPressed && !release )
	{
		if( event.key.code == 15 )
		{
			release = true;
			active = !active;
			
			if( playable )
			{
				click.play();
			}
		}
	}
	
	if( event.type == sf::Event::KeyReleased )
	{
		release = false;
	}
}

void Pausesystem::draw( sf::RenderWindow* &window )
{
	window->draw( blackout.get() );
	window->draw( text.get() );
}

void Pausesystem::fadein( float v, int max )
{
	blackout.fadein( v, max );
	text.fadein( v, max );
}

void Pausesystem::fadeout( float v, int min )
{
	blackout.fadeout( v, min );
	text.fadeout( v, min );
}



bool Pausesystem::isActive()
{
	return active;
}

void Pausesystem::setActive( bool active )
{
	this->active = active;
}

bool Pausesystem::isChanged()
{
	if( changed )
	{
		changed = false;
		return true;
	}
	
	return false;
}

void Pausesystem::setChanged( bool changed )
{
	this->changed = changed;
}

int Pausesystem::getAlpha()
{
	return blackout.getAlpha();
}



void Pausesystem::setPlayable( bool playable )
{
	this->playable = playable;
}

void Pausesystem::setVolume( float volume )
{
	click.setVolume( volume );
}
