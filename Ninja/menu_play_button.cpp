#include "menu_play_button.h"
#include <stdlib.h>

Menu_play_button::Menu_play_button()
{
    state = 0;
}

Menu_play_button::~Menu_play_button()
{
    mySprite.free();
	state = 0;
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

    return true;
}

void Menu_play_button::draw( RenderWindow* &window )
{
    window->draw( mySprite.get() );
}

void Menu_play_button::handle( Event &event )
{
    int x, y;
	
	mySprite.setOffset( 0 );

	if( event.type == Event::MouseMoved )
	{
		x = event.mouseMove.x;
		y = event.mouseMove.y;
			
		if( mySprite.checkCollision( x, y ) )
		{
			mySprite.setOffset( 1 );
			state = 1;
		}
	}

	if( event.type == Event::MouseButtonPressed )
	{
		x = event.mouseButton.x;
		y = event.mouseButton.y;
			
		if( mySprite.checkCollision( x, y ) )
		{
			mySprite.setOffset( 2 );
			state = 2;
		}
	}
}

int Menu_play_button::getBot()
{
	return mySprite.getBot();
}

int Menu_play_button::getState()
{
	return state;
}

void Menu_play_button::fadein( int i, int max )
{
	mySprite.fadein( i, max );
}

void Menu_play_button::fadeout( int i, int min )
{
	mySprite.fadein( i, min );
}