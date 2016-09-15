#include "title.h"
#include <stdlib.h>

Title::Title()
{
    belt = NULL;
}

Title::~Title()
{
	if( belt != NULL )
	{
		delete belt;
		belt = NULL;
	}

	title.free();
}

void Title::load( int screen_w )
{
	belt = new MySprite( "Title-belt" );
    belt->load( "menu/belt.png" );
	belt->setPosition( screen_w/2 - belt->getWidth()/2, 10 );
	
	title.setID( "Title-title" );
	title.setFont( "menu/KGHAPPY.ttf", 80, 0x7F, 0x99, 0x95 );
	title.setText( "Ninja" );
	title.setPosition( screen_w/2 - title.getWidth()/2, 15 );
}

void Title::draw( sf::RenderWindow &window )
{
    window.draw( belt->get() );
	window.draw( title.get() );
}


int Title::getBot()
{
	return belt->getBot();
}

void Title::fadein( int i, int max )
{
	belt->fadein( i, max );
	title.fadein( i, max );
}

void Title::fadeout( int i, int min )
{
	belt->fadeout( i, min );
	title.fadeout( i, min );
}
