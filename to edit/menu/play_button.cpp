#include "play_button.h"
#include <stdlib.h>

Play_button::Play_button()
{
    state = 0;
	play = true;
	
	mySprite = NULL;
}

Play_button::~Play_button()
{
	if( mySprite != NULL )
	{
		delete mySprite;
		mySprite = NULL;
	}

	myText.free();
	state = 0;
	play = true;
	click.free();
}

void Play_button::load( int screen_w, int bot )
{
	mySprite = new MySprite( "Play_button-mySprite" );
	mySprite->load( "menu/blankbutton.png", 4 );
	mySprite->setPosition( screen_w/2 - mySprite->getWidth()/2, bot );
	
	myText.setID( "Play_button-myText" );
	myText.setFont( "menu/KGHAPPY.ttf", 80, 0x82, 0xae, 0x20 );
	myText.setText( "play" );
	myText.setPosition( screen_w/2 - myText.getWidth()/2, bot +20 );
	
	click.setID( "Play_button-click" );
	click.load( "menu/click.wav", 50 );
}

void Play_button::draw( sf::RenderWindow* &window )
{
    window->draw( mySprite->get() );
	window->draw( myText.get() );
}

void Play_button::handle( sf::Event &event )
{
	if( state != 2 && mySprite->getAlpha() == 255 )
	{
		int x, y;
		mySprite->setOffset( 0 );
		
		if( event.type == sf::Event::MouseMoved )
		{
			x = event.mouseMove.x;
			y = event.mouseMove.y;
				
			if( mySprite->checkCollision( x, y ) && state != 2 )
			{
				mySprite->setOffset( 1 );
				state = 1;
			}
		}

		if( event.type == sf::Event::MouseButtonPressed )
		{
			x = event.mouseButton.x;
			y = event.mouseButton.y;
				
			if( mySprite->checkCollision( x, y ) )
			{
				mySprite->setOffset( 2 );
				
				if( play )
					click.play();
				
				state = 2;
			}
		}
	}
}

int Play_button::getBot()
{
	return mySprite->getBot();
}

int Play_button::getX()
{
	return mySprite->getX();
}

int Play_button::getState()
{
	return state;
}

bool Play_button::nextGameState()
{
	if( state == 2 && mySprite->getAlpha() == 0 )
		return true;
	
	return false;
}

void Play_button::fadein( int i, int max )
{
	mySprite->fadein( i, max );
	myText.fadein( i, max );
}

void Play_button::fadeout( int i, int min )
{
	mySprite->fadeout( i, min );
	myText.fadeout( i, min );
}

void Play_button::turn()
{
	play = !play;
}