#include "circlebutton.h"

Circlebutton::Circlebutton()
{
	free();
}

Circlebutton::~Circlebutton()
{
	free();
}

void Circlebutton::free()
{
	button.free();
	active = false;
	changed = false;
	
	click.free();
	playable = true;
}



void Circlebutton::load( string path, bool active )
{
	free();
	
	button.setIdentity( "circlebutton-button" );
	button.load( path, 3 );
	setActive( active );
	
	click.setIdentity( "link_button-chunk" );
	click.load( "sounds/click.wav" );
}

void Circlebutton::set( float x, float y, float x_scale, float y_scale )
{
	button.setScale( x_scale, y_scale );
	button.setPosition( x -button.getWidth(), y -button.getHeight() );
}

void Circlebutton::handle( sf::Event& event )
{
	if( event.type == sf::Event::MouseButtonPressed )
	{
		if( event.mouseButton.button == sf::Mouse::Left )
		{
			if( button.checkCollision( event.mouseButton.x, event.mouseButton.y ) )
			{
				if( playable )
				{
					click.play();
				}
				
				changeActive();
				changed = true;
			}
		}
	}
}

void Circlebutton::draw( sf::RenderWindow* &window, double elapsedTime )
{
	window->draw( button.get() );
}



void Circlebutton::fadein( float v, int max )
{
	button.fadein( v, max );
}

void Circlebutton::fadeout( float v, int min )
{
	button.fadeout( v, min );
}



bool Circlebutton::isActive()
{
	return active;
}

void Circlebutton::setActive( bool active )
{
	this->active = active;
	
	if( active )
	{
		button.setOffset( 1 );
	}
	else
	{
		button.setOffset( 0 );
	}
}

void Circlebutton::changeActive()
{
	active = !active;
	
	if( active )
	{
		button.setOffset( 1 );
	}
	else
	{
		button.setOffset( 0 );
	}
}

bool Circlebutton::isChanged()
{
	if( changed )
	{
		changed = false;
		return true;
	}
	
	return false;
}

void Circlebutton::setChanged( bool changed )
{
	this->changed = changed;
}

float Circlebutton::getLeft()
{
	return button.getLeft();
}



void Circlebutton::setPlayable( bool playable )
{
	this->playable = playable;
}

void Circlebutton::setVolume( float volume )
{
	click.setVolume( volume );
}