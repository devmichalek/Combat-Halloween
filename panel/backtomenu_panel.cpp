/**
    backtomenu_panel.h
    Purpose: class Backtomenu_panel as a simple button with label 'menu'.

    @author Adrian Michalek
    @version 2017.02.27
	@email adrmic98@gmail.com
*/

#include "backtomenu_panel.h"

void Backtomenu_panel::load( int r, int t )
{
	mySprite.setName( "replay_button-mySprite" );
	mySprite.load( "data/menu/blankbutton.png", 4 );
	mySprite.setScale( 0.4, 0.4 );
	mySprite.setPosition( r +10, t );
	
	myText.setName( "replay_button-myText" );
	myText.setFont( "data/menu/BADABB__.TTF", 48, 0x82, 0xae, 0x20 );
	myText.setText( "menu" );
	myText.setPosition( mySprite.getX() +18, t );
	
	click.setID( "replay_button-click" );
	click.load( "data/menu/click.wav", 50 );
}