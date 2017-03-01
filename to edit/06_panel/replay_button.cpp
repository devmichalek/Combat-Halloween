#include "replay_button.h"

void Replay_button::load( int screen_w, int bot )
{
	mySprite.setName( "replay_button-mySprite" );
	mySprite.load( "data/02_menu/blankbutton.png", 4 );
	mySprite.setPosition( screen_w/2 - mySprite.getWidth()/2, bot );
	
	myText.setName( "replay_button-myText" );
	myText.setFont( "data/02_menu/BADABB__.TTF", 108, 0x82, 0xae, 0x20 );
	myText.setText( "replay" );
	myText.setPosition( screen_w/2 - myText.getWidth()/2 +10, bot +3 );
	
	click.setID( "replay_button-click" );
	click.load( "data/02_menu/click.wav", 50 );
}