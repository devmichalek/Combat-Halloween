#include "button.h"

Button::Button()
{
	free();
}

Button::~Button()
{
	free();
}

void Button::free()
{
	button.free();
	locked = false;
	pressed = false;
	
	click.free();
	playable = true;
}



void Button::load( float x, float y, string path, bool locked )
{
	free();
	
	this->locked = locked;
	
	button.setIdentity( "button-button" );
	button.load( path, 3 );
	button.setPosition( x, y );
	
	if( locked )
	{
		button.setOffset( 2 );
	}
	
	click.setIdentity( "link_button-chunk" );
	click.load( "sounds/click.wav" );
}

void Button::setScale( float x, float y )
{
	button.setScale( x, y );
}

void Button::handle( sf::Event& event )
{
	if( !locked )
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
					
					button.setOffset( 1 );
					pressed = true;
				}
			}
		}
	}
}

void Button::draw( sf::RenderWindow* &window )
{
	window->draw( button.get() );
}



void Button::fadein( float v, int max )
{
	button.fadein( v, max );
}

void Button::fadeout( float v, int min )
{
	button.fadeout( v, min );
}

bool Button::isPressed()
{
	return pressed;
}

float Button::getBot()
{
	return button.getBot();
}



void Button::setPlayable( bool playable )
{
	this->playable = playable;
}

void Button::setVolume( float volume )
{
	click.setVolume( volume );
}