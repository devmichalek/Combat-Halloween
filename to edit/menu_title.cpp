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

bool Menu_title::load(int screen_w )
{
    if( !belt.load( "menu/belt.png" ) )
    {
        return false;
    }
    else
    {
        belt.setPosition( screen_w/2 - belt.getWidth()/2, 10 );
    }
	
	if( !title.setFont( "menu/KGHAPPY.ttf", 80, 0x7F, 0x99, 0x95 ) )
	{
		return false;
	}
	else if( !title.setText( "Ninja" ) )
	{
		return false;
	}
	else
	{
		title.setPosition( screen_w/2 - title.getWidth()/2, 15 );
	}

    return true;
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
