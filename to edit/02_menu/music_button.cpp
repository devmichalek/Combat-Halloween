#include "music_button.h"
#include <stdlib.h>

Music_button::Music_button( bool play )
{
    state = 0;
	focus = false;
	this->play = play;
}

Music_button::~Music_button()
{
	button.free();
	scratch.free();
	
	click.free();
	
	focus = false;
	state = 0;
	play = true;
}

void Music_button::load( string path, int bot )
{
	button.setName( "music_button-button" );
    button.load( path, 4 );
	button.setPosition( 10, bot );
	
	scratch.setName( "music_button-scratch" );
	scratch.load( "data/sprites/menu/scratch.png" );
	scratch.setPosition( 10, bot );
	
	click.setID( "music_button-click" );
	click.load( "data/sounds/click.wav", 50 );
}

void Music_button::draw( sf::RenderWindow* &window )
{
    window->draw( button.get() );
	
	if( state == 2 )
		window->draw( scratch.get() );
}

void Music_button::handle( sf::Event &event )
{
	if( button.getAlpha() == 0xFF )
	{
		int x, y;
		button.setOffset( 0 );
		
		if( event.type == sf::Event::MouseMoved )
		{
			x = event.mouseMove.x;
			y = event.mouseMove.y;
					
			if( button.checkCollision( x, y ) )
			{
				button.setOffset( 1 );
			}
			else
				focus = false;
		}
		
		
		if( event.type == sf::Event::MouseButtonPressed && !focus )
		{
			x = event.mouseButton.x;
			y = event.mouseButton.y;
					
			if( button.checkCollision( x, y ) )
			{
				focus = true;
				
				if( play )
					click.play();
					
				if( state == 0 )
					state = 1;
				if( state == 2 )
					state = 3;
			}
		}
		
		if( event.type == sf::Event::MouseButtonReleased )
		{
			focus = false;
		}
		
		if( focus )
			button.setOffset( 2 );
	}
}

int Music_button::getBot()
{
	return button.getBot();
}

bool Music_button::change()
{
	// printf("%d\n", state );
	if( state == 1 )
	{
		state = 2;
		return true;
	}
	
	if( state == 3 )
	{
		state = 0;
		return true;
	}
		
	return false;
}


void Music_button::fadein( int i, int max )
{
	button.fadein( i, max );
	scratch.fadein( i, max );
}

void Music_button::fadeout( int i, int min )
{
	button.fadeout( i, min );
	scratch.fadeout( i, min );
}