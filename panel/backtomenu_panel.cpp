/**
    backtomenu_panel.h
    Purpose: class Backtomenu_panel as a simple button with label 'menu'.

    @author Adrian Michalek
    @version 2017.02.27
	@email adrmic98@gmail.com
*/

#include "backtomenu_panel.h"

void Backtomenu_panel::load( float x, float y )
{
	mySprite.setName( "replay_button-mySprite" );
	mySprite.load( "data/menu/blankbutton.png", 4 );
	mySprite.setScale( 0.4, 0.4 );
	mySprite.setPosition( x +10, y );
	
	myText.setName( "replay_button-myText" );
	myText.setFont( "data/menu/BADABB__.TTF", 48, 0x82, 0xae, 0x20 );
	myText.setText( "menu" );
	myText.setPosition( mySprite.getX() +27, y +2 );
	
	click.setID( "replay_button-click" );
	click.load( "data/menu/click.wav", 50 );
}

void Backtomenu_panel::draw( sf::RenderWindow* &window )
{
    window->draw( mySprite.get() );
	window->draw( myText.get() );
}

void Backtomenu_panel::fadein( int i, int max )
{
	mySprite.fadein( i, max );
	myText.fadein( i, max );
}

void Backtomenu_panel::fadeout( int i, int min )
{
	mySprite.fadeout( i, min );
	myText.fadeout( i, min );
}