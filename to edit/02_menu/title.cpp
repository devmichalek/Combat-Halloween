/**
    title.h
    Purpose: class Title - to show sprite (title).

    @author Adrian Michalek
    @version 2016.10.13
	@email adrmic98@gmail.com
*/

#include "title.h"


Title::Title()
{
    // empty
}

Title::~Title()
{
	belt.free();
	title.free();
}

void Title::load( const int& screen_w )
{
	belt.setName( "title-belt" );
    belt.load( "data/sprites/menu/belt.png" );
	belt.setPosition( screen_w/2 - belt.getWidth()/2, 10 );
	
	title.setName( "title-title" );
	title.setFont( "data/fonts/BADABB__.TTF", 110, 0x7F, 0x99, 0x95 );
	title.setText( "Ninja" );
	title.setPosition( screen_w/2 - title.getWidth()/2, -8 );
}

void Title::draw( sf::RenderWindow &window )
{
    window.draw( belt.get() );
	window.draw( title.get() );
}


const int Title::getBot()
{
	return belt.getBot();
}

void Title::fadein( int i, int max )
{
	belt.fadein( i, max );
	title.fadein( i, max );
}

void Title::fadeout( int i, int min )
{
	belt.fadeout( i, min );
	title.fadeout( i, min );
}
