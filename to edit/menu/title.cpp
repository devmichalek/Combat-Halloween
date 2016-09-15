#include "menu_title.h"
#include <stdlib.h>

Menu_title::Menu_title()
{
    // empty
}

Menu_title::~Menu_title()
{
    belt.free();
	title.free();
}

void Menu_title::load( int screen_w )
{
	belt.setID( "menu_title-belt" );
    belt.load( "menu/belt.png" );
	belt.setPosition( screen_w/2 - belt.getWidth()/2, 10 );
	
	title.setID( "menu_title-title" );
	title.setFont( "menu/KGHAPPY.ttf", 80, 0x7F, 0x99, 0x95 );
	title.setText( "Ninja" );
	title.setPosition( screen_w/2 - title.getWidth()/2, 15 );
}

void Menu_title::draw( sf::RenderWindow &window )
{
    window.draw( belt.get() );
	window.draw( title.get() );
}


int Menu_title::getBot()
{
	return belt.getBot();
}

void Menu_title::fadein( int i, int max )
{
	belt.fadein( i, max );
	title.fadein( i, max );
}

void Menu_title::fadeout( int i, int min )
{
	belt.fadeout( i, min );
	title.fadeout( i, min );
}
