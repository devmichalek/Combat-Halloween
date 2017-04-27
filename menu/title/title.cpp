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
	title.free();
	title_sec.free();
	version.free();
}



void Title::load( unsigned w, unsigned h )
{
	free();
	
	background.setName( "title-background" );
	background.load( "data/menu/background.png" );
	
	belt.setName( "title-belt" );
    belt.load( "data/menu/belt.png" );
	
	title.setName( "title-title" );
	title.setFont( "data/menu/BADABB__.TTF", 50, 0x7F, 0x99, 0x95 );
	title.setText( "Assassin's" );
	
	title_sec.setName( "title-title" );
	title_sec.setFont( "data/menu/BADABB__.TTF", 50, 0x7F, 0x99, 0x95 );
	title_sec.setText( "Genesis" );
	
	version.setName( "title-version" );
	version.setFont( "data/menu/BADABB__.TTF", 15, 0xFF, 0xFF, 0xFF );
	version.setText( "Alpha Testing" );
	
	setView( w, h, 0, 0 );
}

void Title::draw( sf::RenderWindow &window )
{
	window.draw( background.get() );
    window.draw( belt.get() );
	window.draw( title.get() );
	window.draw( title_sec.get() );
	window.draw( version.get() );
}



void Title::fadein( int i, int max )
{
	background.fadein( i, max );
	belt.fadein( i, max );
	title.fadein( i, max );
	title_sec.fadein( i, max );
	version.fadein( i, max );
}

void Title::fadeout( int i, int min )
{
	background.fadeout( i, min );
	belt.fadeout( i, min );
	title.fadeout( i, min );
	title_sec.fadeout( i, min );
	version.fadeout( i, min );
}



const int Title::getBot() const
{
	return belt.getBot();
}

sf::Uint8 Title::getAlpha()
{
	return background.getAlpha();
}



void Title::setScale( float s_x, float s_y )
{
	background.setBasicScale( s_x, s_y );
	background.setScale();
	
	belt.setBasicScale( s_x, s_y );
	belt.setScale();
	
	title.setBasicScale( s_x, s_y );
	title.setScale();
	
	title_sec.setBasicScale( s_x, s_y );
	title_sec.setScale();
	
	version.setBasicScale( s_x, s_y );
	version.setScale();
}

void Title::setView( unsigned w, unsigned h, int r_x, int r_y )
{
	background.setPosition( w/2 -background.getWidth()/2 +r_x, h/2 -background.getHeight()/2 +r_y );
	belt.setPosition( w/2 - belt.getWidth()/2 +r_x, 10 *belt.getYScale() +r_y );
	title.setPosition( w/2 - title.getWidth() /2 -(30 *title.getXScale()) +r_x, (14 *title.getYScale()) +r_y );
	title_sec.setPosition( w/2 -(5 *title_sec.getXScale()) +r_x, title.getBot() );
	version.setPosition( belt.getRight() -version.getWidth() -(170 *version.getXScale()), belt.getBot() -(35 *version.getYScale()) );
}