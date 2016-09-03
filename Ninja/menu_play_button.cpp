#include "menu_play_button.h"
#include <stdlib.h>

Menu_play_button::Menu_play_button()
{
    state = 0;
	play = true;
}

Menu_play_button::~Menu_play_button()
{
    mySprite.free();
	myText.free();
	state = 0;
	play = true;
	click.free();
}

bool Menu_play_button::load( int screen_w, int bot )
{
    if( !mySprite.load( "menu/blankbutton.png", 4 ) )
    {
        return false;
    }
    else
    {
        mySprite.setPosition( screen_w/2 - mySprite.getWidth()/2, bot );
    }
	
	if( !myText.setFont( "menu/KGHAPPY.ttf", 80, 0x82, 0xae, 0x20 ) )
	{
		return false;
	}
	else if( !myText.setText( "play" ) )
	{
		return false;
	}
	else
	{
		myText.setPosition( screen_w/2 - myText.getWidth()/2 +50, bot +20 );
	}
	
	if( !click.load( "menu/click.wav", 50 ) )
	{
		return false;
	}

    return true;
}

void Menu_play_button::draw( sf::RenderWindow* &window )
{
    window->draw( mySprite.get() );
	window->draw( myText.get() );
}

void Menu_play_button::handle( sf::Event &event )
{
	if( state != 2 && mySprite.getAlpha() == 255 )
	{
		int x, y;
		mySprite.setOffset( 0 );
		
		if( event.type == sf::Event::MouseMoved )
		{
			x = event.mouseMove.x;
			y = event.mouseMove.y;
				
			if( mySprite.checkCollision( x, y ) && state != 2 )
			{
				mySprite.setOffset( 1 );
				state = 1;
			}
		}

		if( event.type == sf::Event::MouseButtonPressed )
		{
			x = event.mouseButton.x;
			y = event.mouseButton.y;
				
			if( mySprite.checkCollision( x, y ) )
			{
				mySprite.setOffset( 2 );
				
				if( play )
					click.play();
				
				state = 2;
			}
		}
	}
}

int Menu_play_button::getBot()
{
	return mySprite.getBot();
}

int Menu_play_button::getX()
{
	return mySprite.getX();
}

int Menu_play_button::getState()
{
	return state;
}

bool Menu_play_button::nextGameState()
{
	if( state == 2 && mySprite.getAlpha() == 0 )
		return true;
	
	return false;
}

void Menu_play_button::fadein( int i, int max )
{
	mySprite.fadein( i, max );
	myText.fadein( i, max );
}

void Menu_play_button::fadeout( int i, int min )
{
	mySprite.fadeout( i, min );
	myText.fadeout( i, min );
}

void Menu_play_button::turn()
{
	play = !play;
}