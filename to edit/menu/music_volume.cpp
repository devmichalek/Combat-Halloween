#include "music_volume.h"

Music_volume::Music_volume( int volume )
{
	this->volume = volume;
	last_volume = 1;
}

Music_volume::~Music_volume()
{
	volume = 1;
	last_volume = 1;
	green_bar.free();
	white_bar.free();
	text.free();
}

	
void Music_volume::load( int screen_w, int screen_h, string str )
{
	white_bar.create( 128*3, 40, 0xFF, 0xFF, 0xFF );
	white_bar.setPosition( screen_w/3 + white_bar.getWidth()/2, screen_h/2 - white_bar.getHeight()/2 );
	
	green_bar.create( volume*3, 40, 0x70, 0xB7, 0x59 );
	green_bar.setPosition( screen_w/3 + green_bar.getWidth()/2, screen_h/2 - green_bar.getHeight()/2 );
	
	text.setFont( "intro/Jaapokki-Regular.otf", 30, 0xFF, 0xFF, 0xFF  );
	text.setText( str );
	text.setPosition( screen_w/3, screen_h/2 - text.getHeight()/2 );
}

void Music_volume::draw( sf::RenderWindow* &window )
{
	window->draw( white_bar.get() );
	window->draw( green_bar.get() );
	window->draw( text.get() );
	
	if( last_volume != volume )
	{
		last_volume = volume;
		green_bar.create( volume*3, 40, 0x70, 0xB7, 0x59 );
	}
}

void Music_volume::handle( sf::Event &event )
{
	
	
}

void Music_volume::fadein( int i, int max )
{
	white_bar.fadein( i, max );
	green_bar.fadein( i, max );
	text.fadein( i, max );
}

void Music_volume::fadeout( int i, int min )
{
	white_bar.fadeout( i, min );
	green_bar.fadeout( i, min );
	text.fadeout( i, min );
}