#include "pause.h"

Pause::Pause()
{
	free();
}

Pause::~Pause()
{
	free();
}

void Pause::free()
{
	text.free();
	sprite.free();
	focus = false;
	paused = false;
	allowed = false;
}


void Pause::load( int screen_w, int screen_h )
{
	free();
	
	text.setName( "pause-text" );
	text.setFont( "data/00_loading/Jaapokki-Regular.otf", 100, 255, 255, 255 );
	text.setText( "Paused" );
	text.setPosition( screen_w/2 -text.getWidth()/2, screen_h/2 -text.getHeight()/2 -40 );
	text.setAlpha( 225 );
	
	sprite.setName( "pause-sprite" );
	sprite.create( screen_w, screen_h );
	sprite.setColor( sf::Color( 0, 0, 0, 180 ) );
	sprite.setAlpha( 180 );
}

void Pause::draw( sf::RenderWindow* &window )
{
	if( paused )
	{
		window->draw( sprite.get() );
		window->draw( text.get() );
	}
}

void Pause::handle( sf::Event& event )
{
	if( allowed )
	{
		if( event.type == sf::Event::KeyPressed && !focus )
		{
			if( event.key.code == 15 )
			{
				focus = true;
				paused = !paused;
			}
		}
		else if( event.type == sf::Event::KeyReleased )
		{
			if( event.key.code == 15 )
			{
				focus = false;
			}
		}
	}
	
	if( paused )
	{
		allowed = true;
	}
	else
	{
		allowed = false;
	}
}


bool Pause::isPaused()
{
	return paused;
}

void Pause::allow()
{
	allowed = true;
}