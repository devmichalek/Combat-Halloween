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
	scale = 0;
}



void Play_button::load( unsigned w, unsigned h )
{
	scale = 0.9;
	
	mySprite.setName( "play_button-mySprite" );
	mySprite.load( "data/menu/play.png", 4 );
	
	setView( w, h, 0, 0 );
	
	click.setID( "play_button-click" );
	click.load( "data/menu/sfx.wav", 50 );
}

void Play_button::draw( sf::RenderWindow* &window )
{
    window->draw( mySprite.get() );
}

void Play_button::handle( sf::Event &event, int r_x, int r_y )
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
					
				if( mySprite.checkCollision( x +r_x, y +r_y ) )
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
					
				if( mySprite.checkCollision( x +r_x, y +r_y ) )
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



bool Play_button::nextState() const
{
	if( state == 2 && mySprite.getAlpha() == 0 )
	{
		return true;
	}
	
	return false;
}



void Play_button::setScale( float s_x, float s_y )
{
	mySprite.setBasicScale( s_x, s_y );
	mySprite.setScale( scale, scale );
}

void Play_button::setView( unsigned w, unsigned h, int r_x, int r_y )
{
	mySprite.setPosition( w/2 - mySprite.getWidth()/2 +r_x, h /1.875 +r_y );
}