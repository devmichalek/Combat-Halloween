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



void Nick::load( int screen_w, int screen_h )
{
	free();
	
	label.setName( "nick-label" );
	label.load( "data/02_menu/fancy_label.png" );
	label.setPosition( screen_w -label.getWidth() -5, screen_h -label.getHeight() );
	
	text.setName( "nick-text" );
	text.setFont( "data/00_loading/Jaapokki-Regular.otf", 15, 0xFF, 0xFF, 0xFF );
	setNick();
}

void Nick::draw( sf::RenderWindow &window )
{
	window.draw( label.get() );
	window.draw( text.get() );
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
