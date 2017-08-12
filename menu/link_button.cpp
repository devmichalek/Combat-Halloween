#include "link_button.h"

Link_button::Link_button()
{
	free();
}

Link_button::~Link_button()
{
	free();
}

void Link_button::free()
{
	button.free();
	click.free();
}



void Link_button::load( float x, float y, string path )
{
	free();
	
	button.setIdentity( "link_button-button" );
	button.load( path, 3 );
	button.setPosition( x, y );
	
	click.setIdentity( "link_button-chunk" );
	click.load( "sounds/click.wav" );
}

void Link_button::setScale( float x, float y )
{
	button.setScale( x, y );
}

void Link_button::setUrl( string url )
{
	this->url = url;
}

void Link_button::handle( sf::Event& event )
{
	if( event.type == sf::Event::MouseButtonPressed )
	{
		if( event.mouseButton.button == sf::Mouse::Left )
		{
			// printf( "%d %d\n", event.mouseButton.x, event.mouseButton.y );
			if( button.checkCollisionCircle( event.mouseButton.x, event.mouseButton.y ) )
			{
				click.play();
				button.setOffset( 1 );
				string command = "start " +url;
				system( command.c_str() );
			}
		}
	}
	
	if( event.type == sf::Event::MouseMoved )
	{
		button.setOffset( 0 );
	}
}

void Link_button::draw( sf::RenderWindow* &window )
{
	window->draw( button.get() );
}



void Link_button::fadein( float v, int max )
{
	button.fadein( v, max );
}

void Link_button::fadeout( float v, int min )
{
	button.fadeout( v, min );
}

float Link_button::getRight()
{
	return button.getRight();
}

void Link_button::setPlayable( bool playable )
{
	click.setPlayable( playable );
}

void Link_button::setVolume( float volume )
{
	click.setVolume( volume );
}