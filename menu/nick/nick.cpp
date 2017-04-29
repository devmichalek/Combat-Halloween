/**
    nick.h
    Purpose: class Nick to show nick in menu state.

    @author Adrian Michalek
    @version 2017.03.27
	@email adrmic98@gmail.com
*/

#include "nick.h"
#include "file/file.h"

Nick::Nick()
{
	free();
}

Nick::~Nick()
{
	free();
}

void Nick::free()
{
	text.free();
	label.free();
}



void Nick::load( unsigned screen_w, unsigned screen_h )
{
	free();
	
	label.setName( "nick-label" );
	label.load( "data/initialization/fancy_label.png" );
	label.setScale( 0.35, 0.35 );
	label.setPosition( screen_w -label.getWidth() -5, screen_h -label.getHeight() );
	
	text.setName( "nick-text" );
	text.setFont( "data/initialization/Jaapokki-Regular.otf", 13, 0xFF, 0xFF, 0xFF );
	
	setNick();
}

void Nick::draw( sf::RenderWindow &window )
{
	window.draw( label.get() );
	window.draw( text.get() );
}



void Nick::fadein( int i, int max )
{
	label.fadein( i, max );
	text.fadein( i, max );
}

void Nick::fadeout( int i, int min )
{
	label.fadeout( i, min );
	text.fadeout( i, min );
}



void Nick::setNick()
{
	// Set text.
	MyFile file;
	file.load( "data/txt/nick/nick_current.txt" );
	if( file.is_good() )
	{
		string line;
		file.get() >> line;
		text.setText( line );
	}
	file.free();
	text.center( label.getWidth(), label.getHeight(), label.getX(), label.getY() );
}