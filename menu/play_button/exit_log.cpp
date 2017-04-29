/**
    exit_log.h
    Purpose: class Exit_log to show exit state.

    @author Adrian Michalek
    @version 2016.10.27
	@email adrmic98@gmail.com
*/

#include "exit_log.h"

Exit_log::Exit_log()
{
	free();
}

Exit_log::~Exit_log()
{
	free();
}

void Exit_log::free()
{
	state = 0;
	
	mySprite.free();
	myText.free();
	
	play = true;
	click.free();
}


void Exit_log::load( unsigned screen_w, unsigned screen_h )
{
	mySprite.setName( "exit_log-mySprite" );
    mySprite.load( "data/menu/exit.png" );
	mySprite.setAlpha( 0xFF );
	mySprite.setScale( 0.4, 0.4 );
	mySprite.setPosition( screen_w /2 -mySprite.getWidth() /2, screen_h /2 -mySprite.getHeight() /2 );
	
	myText.setName( "exit_log-myText" );
	myText.setFont( "data/menu/BADABB__.TTF", 33, 0xFF, 0xFF, 0xFF );
	myText.setText( "q-quit    b-back" );
	myText.setAlpha( 0xFF );
	myText.setPosition( screen_w /2 -myText.getWidth() /2, screen_h /2 -myText.getHeight() /2 -6 );

	click.setID( "exit_log-click" );
	click.load( "data/menu/click.wav", 50 );
}

void Exit_log::handle( sf::Event &event )
{
	static bool rel = false;
	
	if( event.type == sf::Event::KeyPressed && state < 2 )
	{
		if( !rel )
		{
			rel = true;
			if( event.key.code == sf::Keyboard::Q )
			{
				if( play )
				{
					click.play();
				}
				
				if( state == 0 )
				{
					state = 1;
				}
				else if( state == 1 )
				{
					state = 2;
				}
					
			}
			else if( event.key.code == sf::Keyboard::B )
			{
				if( state == 1 )
				{
					if( play )
					{
						click.play();
					}
						
					state = 0;
				}
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



void Exit_log::fadein( int i, int max )
{
	mySprite.fadein( i, max );
	myText.fadein( i, max );
}

void Exit_log::fadeout( int i, int min )
{
	mySprite.fadeout( i, min );
	myText.fadeout( i, min );
}



int Exit_log::getState()
{
	return state;
}