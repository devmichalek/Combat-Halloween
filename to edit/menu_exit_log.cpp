#include "menu_exit_log.h"


bool Menu_exit_log::load( int screen_w, int screen_h )
{
    if( !mySprite.load( "menu/exit.png" ) )
    {
        return false;
    }
    else
    {
		mySprite.setAlpha( 255 );
        mySprite.setPosition( screen_w/2 - mySprite.getWidth()/2, screen_h/2 - mySprite.getHeight()/2 );
    }
	
	if( !myText.setFont( "menu/KGHAPPY.ttf", 33, 0xFF, 0xFF, 0xFF ) )
	{
		return false;
	}
	else if( !myText.setText( "q-quit  b-back" ) )
	{
		return false;
	}
	else
	{
		myText.setAlpha( 255 );
		myText.setPosition( screen_w/2 - myText.getWidth()/2, screen_h/2 - myText.getHeight()/2 -6 );
	}
	
	if( !click.load( "menu/click.wav", 50 ) )
	{
		return false;
	}

    return true;
}

void Menu_exit_log::handle( sf::Event &event )
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

void Menu_exit_log::draw( sf::RenderWindow* &window )
{
	if( state > 0 )
	{
		window->draw( mySprite.get() );
		window->draw( myText.get() );
	}
}


int Menu_exit_log::getState()
{
	return state;
}