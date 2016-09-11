#include "play_exit_log.h"


void Play_exit_log::load( int screen_w, int screen_h )
{
	mySprite.setID( "menu_exit_log-mySprite" );
    mySprite.load( "menu/exit.png" );
	mySprite.setAlpha( 255 );
	mySprite.setPosition( screen_w/2 - mySprite.getWidth()/2, screen_h/2 - mySprite.getHeight()/2 );

	mySprite.setID( "menu_exit_log-myText" );
	myText.setFont( "menu/KGHAPPY.ttf", 33, 0xFF, 0xFF, 0xFF );
	myText.setText( "q-quit  b-back" );
	myText.setAlpha( 255 );
	myText.setPosition( screen_w/2 - myText.getWidth()/2, screen_h/2 - myText.getHeight()/2 -6 );

	mySprite.setID( "menu_exit_log-click" );
	click.load( "menu/click.wav", 50 );
}

void Play_exit_log::handle( sf::Event &event )
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
			if( play )
				click.play();
			
			if( state == 1 )
				state = 0;
		}
	}
	else if( event.type == sf::Event::KeyReleased )
	{
		rel = false;
	}
}

void Play_exit_log::draw( sf::RenderWindow* &window )
{
	if( state > 0 )
	{
		window->draw( mySprite.get() );
		window->draw( myText.get() );
	}
}


int Play_exit_log::getState()
{
	return state;
}