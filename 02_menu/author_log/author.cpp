#include "author.h"

Author::Author()
{
	free();
}

Author::~Author()
{
	free();
}

void Author::free()
{
	scroll.free();
	list.free();
	author_info.free();
	reset_done = false;
}

void Author::reset()
{
	if( !reset_done )
	{
		reset_done = true;
		scroll.reset();
		list.reset();
		author_info.reset();
	}
}



void Author::load( int screen_w, int screen_h )
{
	free();
	
	scroll.load( screen_w, screen_h );
	list.load( screen_w, screen_h );
	author_info.load( screen_w, screen_h );
}

void Author::draw( sf::RenderWindow* &window )
{
	reset_done = false;
	
	scroll.draw( window );
	list.draw( window );
	author_info.draw( window );
	
	if( scroll.isMoved() )
	{
		list.move( scroll.getDistance() );
		author_info.move( scroll.getDistance() );
	}
}

void Author::handle( sf::Event &event )
{
	scroll.handle( event );
	list.handle( event );
}



void Author::fadein( int i, int max )
{
	scroll.fadein( i, max );
	list.fadein( i, max );
	author_info.fadein( i, max );
}

void Author::fadeout( int i, int min )
{
	scroll.fadeout( i, min );
	list.fadeout( i, min );
	author_info.fadeout( i, min );
}
