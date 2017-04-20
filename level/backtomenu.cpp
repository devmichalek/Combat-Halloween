/**
    backtomenu.h
    Purpose: class Backtomenu - button with function "back to menu".

    @author Adrian Michalek
    @version 2016.12.05
	@email adrmic98@gmail.com
*/

#include "backtomenu.h"

void Backtomenu::load( int screen_w )
{
	button.setName( "backtomenu-backtomenu" );
    button.load( "data/menu/backtomenu.png", 4 );

	if( locked )
	{
		button.setOffset( 3 );    // locked offset = 3
	}
		
	button.setScale( 0.5, 0.5 );
	button.setPosition( screen_w - button.getWidth() -20, 20 );
	
	click.setID( "backtomenu-click" );
	click.load( "data/menu/click.wav", 50 );
	
	state = 0;
}

void Backtomenu::handle( sf::Event &event )
{
	if( !locked )
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
				{
					focus = false;
				}
			}

			if( event.type == sf::Event::MouseButtonPressed )
			{
				x = event.mouseButton.x;
				y = event.mouseButton.y;
					
				if( button.checkCollision( x, y ) )
				{
					button.setOffset( 2 );
						
					if( play )
					{
						click.play();
					}
					
					focus = true;
					
					if( state == 1 )
					{
						state = 2;
					}
					else if( state == 0 )
					{
						state = -1;
					}

				}
			}
				
			if( event.type == sf::Event::MouseButtonReleased )
			{
				focus = false;
			}
				
			if( focus )
			{
				button.setOffset( 2 );
			}
		}
	}
}



void Backtomenu::setState( int state )
{
	button.setOffset( 0 );
	this->state = state;
}

int Backtomenu::getState()
{
	return state;
}