/**
    backtomenu_panel.h
    Purpose: class Backtomenu_panel as a simple button with label 'menu'.

    @author Adrian Michalek
    @version 2017.02.27
	@email adrmic98@gmail.com
*/

#include "backtomenu_panel.h"

void Backtomenu_panel::load( int screen_w, int bot )
{
	mySprite.setName( "replay_button-mySprite" );
	mySprite.load( "data/02_menu/blankbutton.png", 4 );
	mySprite.setPosition( screen_w/2 - mySprite.getWidth()/2, bot );
	
	myText.setName( "replay_button-myText" );
	myText.setFont( "data/02_menu/BADABB__.TTF", 120, 0x82, 0xae, 0x20 );
	myText.setText( "menu" );
	myText.setPosition( screen_w/2 - myText.getWidth()/2 +10, bot -3 );
	
	click.setID( "replay_button-click" );
	click.load( "data/02_menu/click.wav", 50 );
}