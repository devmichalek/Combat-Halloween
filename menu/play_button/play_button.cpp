/**
    play_button.h
    Purpose: class Play_button - for button 'play' to start game, contain state.

    @author Adrian Michalek
    @version 2016.10.03
	@email adrmic98@gmail.com
*/

#include "play_button.h"


Play_button::Play_button()
{
	free();
}

Play_button::~Play_button()
{
	free();
}

void Play_button::free()
{
	state = 0;
	
	mySprite.free();
	
	play = true;
	click.free();
}



void Play_button::load( unsigned screen_w, unsigned screen_h )
{
	mySprite.setName( "play_button-mySprite" );
	mySprite.load( "data/menu/play.png", 4 );
	mySprite.setPosition( screen_w/2 - mySprite.getWidth()/2, screen_h /1.875 );
	
	click.setID( "play_button-click" );
	click.load( "data/menu/sfx.wav", 50 );
}

void Play_button::draw( sf::RenderWindow* &window )
{
    window->draw( mySprite.get() );
}

void Play_button::handle( sf::Event &event )
{
	if( state != 2 )
	{
		if( mySprite.getAlpha() == 0xFF )
		{
			int x, y;
			mySprite.setOffset( 0 );
			
			if( event.type == sf::Event::MouseMoved )
			{
				x = event.mouseMove.x;
				y = event.mouseMove.y;
					
				if( mySprite.checkCollision( x, y ) )
				{
					if( state != 2 )
					{
						state = 1;
						mySprite.setOffset( 1 );
					}
				}
			}

			if( event.type == sf::Event::MouseButtonPressed )
			{
				x = event.mouseButton.x;
				y = event.mouseButton.y;
					
				if( mySprite.checkCollision( x, y ) )
				{
					state = 2;
					mySprite.setOffset( 2 );
					
					if( play )
					{
						click.play();
					}
				}
			}
		}
	}
}



void Play_button::fadein( int i, int max )
{
	mySprite.fadein( i, max );
}

void Play_button::fadeout( int i, int min )
{
	mySprite.fadeout( i, min );
}



void Play_button::setState( int state )
{
	mySprite.setOffset( 0 );
	this->state = state;
}



const float Play_button::getBot() const
{
	return mySprite.getBot();
}

const float Play_button::getX() const
{
	return mySprite.getX();
}

const sf::Uint8& Play_button::getState() const
{
	return state;
}



bool Play_button::nextState() const
{
	if( state == 2 && mySprite.getAlpha() == 0 )
	{
		return true;
	}
	
	return false;
}