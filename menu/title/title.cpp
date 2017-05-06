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
    free();
}

Title::~Title()
{
	free();
}

void Title::free()
{
	background.free();
	belt.free();
	// title.free();
	// title_sec.free();
	// version.free();
}



void Title::load( unsigned screen_w, unsigned screen_h )
{
	free();
	
	background.setName( "title-background" );
	background.load( "data/menu/background.png" );
	background.setPosition( screen_w/2 -background.getWidth()/2, screen_h/2 -background.getHeight()/2 );
	
	belt.setName( "title-belt" );
    belt.load( "data/menu/belt.png" );
	belt.setScale( 0.55, 0.55 );
	belt.setPosition( screen_w/2 - belt.getWidth()/2, 10 );
	
	/*
	title.setName( "title-title" );
	title.setFont( "data/menu/BADABB__.TTF", 50, 0x7F, 0x99, 0x95 );
	title.setText( "Assassin's" );
	title.setPosition( screen_w/2 - title.getWidth() /2 -30, 14 );
	
	title_sec.setName( "title-title" );
	title_sec.setFont( "data/menu/BADABB__.TTF", 50, 0x7F, 0x99, 0x95 );
	title_sec.setText( "Genesis" );
	title_sec.setPosition( screen_w/2 -5, title.getBot() );
	
	version.setName( "title-version" );
	version.setFont( "data/menu/BADABB__.TTF", 15, 0xFF, 0xFF, 0xFF );
	version.setText( "Alpha Testing" );
	version.setPosition( belt.getRight() -version.getWidth() -170, belt.getBot() -35 );
	*/
}

void Title::draw( sf::RenderWindow &window )
{
	window.draw( background.get() );
    window.draw( belt.get() );
	// window.draw( title.get() );
	// window.draw( title_sec.get() );
	// window.draw( version.get() );
}



void Title::fadein( int i, int max )
{
	background.fadein( i, max );
	belt.fadein( i, max );
	// title.fadein( i, max );
	// title_sec.fadein( i, max );
	// version.fadein( i, max );
}

void Title::fadeout( int i, int min )
{
	background.fadeout( i, min );
	belt.fadeout( i, min );
	// title.fadeout( i, min );
	// title_sec.fadeout( i, min );
	// version.fadeout( i, min );
}



const int Title::getBot() const
{
	return belt.getBot();
}

sf::Uint8 Title::getAlpha()
{
	return background.getAlpha();
}