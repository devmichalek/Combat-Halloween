#include "exit_log.h"


void Exit_log::load( int screen_w, int screen_h )
{
	mySprite.setName( "menu_exit_log-mySprite" );
    mySprite.load( "data/sprites/menu/exit.png" );
	mySprite.setAlpha( 255 );
	mySprite.center( 0, 0, screen_w, screen_h );

	myText.setName( "menu_exit_log-myText" );
	myText.setFont( "data/fonts/BADABB__.TTF", 33, 0xFF, 0xFF, 0xFF );
	myText.setText( "q-quit  b-back" );
	myText.setAlpha( 255 );
	myText.center( screen_w, screen_h, 0, -6 );

	click.setID( "menu_exit_log-click" );
	click.load( "data/sounds/click.wav", 50 );
}

void Exit_log::handle( sf::Event &event )
{
	static bool rel = false;
	if( event.type == sf::Event::KeyPressed && !rel && state < 2 )
	{
		rel = true;
		if( event.key.code == sf::Keyboard::Q )
		{
			if( play )
				click.play();
				
			if( state == 0 )
				state = 1;
			else if( state == 1 )
				state = 2;
		}
		else if( event.key.code == sf::Keyboard::B )
		{
			if( state == 1 )
			{
				if( play )
					click.play();
				state = 0;
			}
		}
	}
	else if( event.type == sf::Event::KeyReleased )
	{
		rel = false;
	}
}

void Exit_log::draw( sf::RenderWindow* &window )
{
	if( state > 0 )
	{
		window->draw( mySprite.get() );
		window->draw( myText.get() );
	}
}


int Exit_log::getState()
{
	return state;
}