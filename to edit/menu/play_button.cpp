#include "play_button.h"
#include <stdlib.h>

Play_button::Play_button()
{
    state = 0;
	play = true;
}

Play_button::~Play_button()
{
	mySprite.free();
	myText.free();
	
	state = 0;
	play = true;
	click.free();
}

void Play_button::load( int screen_w, int bot )
{
	mySprite.setName( "play_button-mySprite" );
	mySprite.load( "data/sprites/menu/blankbutton.png", 4 );
	mySprite.setPosition( screen_w/2 - mySprite.getWidth()/2, bot );
	
	myText.setName( "play_button-myText" );
	myText.setFont( "data/fonts/BADABB__.TTF", 130, 0x82, 0xae, 0x20 );
	myText.setText( "play" );
	myText.setPosition( screen_w/2 - myText.getWidth()/2 +10, bot -5 );
	
	click.setID( "play_button-click" );
	click.load( "data/sounds/click.wav", 50 );
}

void Play_button::draw( sf::RenderWindow* &window )
{
    window->draw( mySprite.get() );
	window->draw( myText.get() );
}

void Play_button::handle( sf::Event &event )
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

const int Play_button::getBot() const
{
	return mySprite.getBot();
}

const int Play_button::getX() const
{
	return mySprite.getX();
}

const sf::Uint8& Play_button::getState() const
{
	return state;
}

bool Play_button::nextGameState() const
{
	if( state == 2 && mySprite.getAlpha() == 0 )
		return true;
	
	return false;
}

void Play_button::fadein( int i, int max )
{
	mySprite.fadein( i, max );
	myText.fadein( i, max );
}

void Play_button::fadeout( int i, int min )
{
	mySprite.fadeout( i, min );
	myText.fadeout( i, min );
}

void Play_button::setState( const  int s )
{
	mySprite.setOffset( 0 );
	state = s;
}