#include "backtomenu.h"


void Backtomenu::load( int screen_w )
{
	button.setName( "link_button-backtomenu" );
    button.load( "data/sprites/menu/backtomenu.png", 4 );

	if( locked )
		button.setOffset( 3 );    // locked offset = 3
		
	button.setScale( 0.5, 0.5 );
	button.setPosition( screen_w - button.getWidth() -20, 20 );
	
	click.setID( "backtomenu-click" );
	click.load( "data/sounds//click.wav", 50 );
	
	state = 0;
}

void Backtomenu::handle( sf::Event &event )
{
	if( !locked && button.getAlpha() == 255 )
	{
		int x, y;
		button.setOffset( 0 );

		if( event.type == sf::Event::MouseMoved )
		{
			x = event.mouseMove.x;
			y = event.mouseMove.y;
				
			if( button.checkCollision( x, y ) )
				button.setOffset( 1 );
			else
				focus = false;
		}

		if( event.type == sf::Event::MouseButtonPressed )
		{
			x = event.mouseButton.x;
			y = event.mouseButton.y;
				
			if( button.checkCollision( x, y ) )
			{
				button.setOffset( 2 );
					
				if( play )
					click.play();
						
				focus = true;
				
				if( state == 1 )
					state = 2;
				else if( state == 0 )
					state = -1;
			}
		}
			
		if( event.type == sf::Event::MouseButtonReleased )
			focus = false;
			
		if( focus )
			button.setOffset( 2 );
	}
}

void Backtomenu::setState( int here )
{
	state = here;
}

int Backtomenu::getState()
{
	return state;
}