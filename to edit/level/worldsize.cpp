#include "level/worldsize.h"

Worldsize::Worldsize()
{
	
}

Worldsize::~Worldsize()
{
	text.free();
}

void Worldsize::load( int screen_w, int screen_h )
{
	text.setName( "Worldsize-text" );
	text.setFont( "data/fonts/Jaapokki-Regular.otf", 40, 0xFF, 0xFF, 0xFF );
	text.setText( "Set length" );
	text.setPosition( screen_w/2 -text.getWidth()/2, screen_h/2 - text.getHeight()/2 );
}

void Worldsize::handle( sf::Event &event )
{
	
}

void Worldsize::draw( sf::RenderWindow &window )
{
	window.draw( text.get() );
}

	
void Worldsize::fadein( int j, int max )
{
	text.fadein( j, max );
}

void Worldsize::fadeout( int j, int min )
{
	text.fadeout( j, min );
}


int Worldsize::getResult()
{
	
}

void Worldsize::reset()
{
	
}

	
bool Worldsize::move( int vel, int ran )
{
	text.setPosition( screen_w/2 -text.getWidth()/2, screen_h/2 - text.getHeight()/2 );
}
