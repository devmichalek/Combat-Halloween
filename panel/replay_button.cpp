/**
    replay_button.h
    Purpose: class Replay_button as a simple button with label 'replay'.

    @author Adrian Michalek
    @version 2017.02.01
	@email adrmic98@gmail.com
*/

#include "replay_button.h"

void Replay_button::load( float x )
{
	mySprite.setName( "replay_button-mySprite" );
	mySprite.load( "data/menu/blankbutton.png", 4 );
	mySprite.setScale( 0.4, 0.4 );
	mySprite.setPosition( 10, x -10 -mySprite.getHeight() );
	
	myText.setName( "replay_button-myText" );
	myText.setFont( "data/menu/BADABB__.TTF", 40, 0x82, 0xae, 0x20 );
	myText.setText( "replay" );
	myText.setPosition( mySprite.getX() +27, mySprite.getY() +7 );
	
	click.setID( "replay_button-click" );
	click.load( "data/menu/click.wav", 50 );
}

int Replay_button::getRight()
{
	return mySprite.getRight();
}

int Replay_button::getTop()
{
	return mySprite.getTop();
}