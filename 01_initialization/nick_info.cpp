#include "nick_info.h"

Nick_info::Nick_info()
{
	free();
}

Nick_info::~Nick_info()
{
	free();
}

void Nick_info::free()
{
	text.free();
	text2.free();
	text3.free();
}



void Nick_info::load( int screen_w, int screen_h )
{
	free();
	
	text.setName( "nick_setter-text" );
	text.setFont( "data/00_loading/Jaapokki-Regular.otf", 40, 0xFF, 0xFF, 0xFF );
	text.setText( "Before we get started, set your nick"  );
	text.setPosition( screen_w /2 -text.getWidth() /2, screen_h /3.5 );
	
	text2.setName( "nick_setter-text2" );
	text2.setFont( "data/00_loading/Jaapokki-Regular.otf", 40, 0xFF, 0xFF, 0xFF );
	text2.setText( "then press enter to continue"  );
	text2.setPosition( screen_w /2 -text2.getWidth() /2, screen_h /1.7 );
	
	text3.setName( "nick_setter-text3" );
	text3.setFont( "data/00_loading/Jaapokki-Regular.otf", 20, 0xFF, 0xFF, 0xFF );
	text3.setText( "a-z, 1-9, no space, 3-11 small characters" );
	text3.setPosition( 5, screen_h -text3.getHeight() -8 );
}

void Nick_info::draw( sf::RenderWindow* &window )
{
	window->draw( text.get() );
	window->draw( text2.get() );
	window->draw( text3.get() );
}



void Nick_info::fadein( int i, int max )
{
	text.fadein( i, max );
	text2.fadein( i, max );
	text3.fadein( i, max );
}

void Nick_info::fadeout( int i, int min )
{
	text.fadeout( i, min );
	text2.fadeout( i, min );
	text3.fadeout( i, min );
}
