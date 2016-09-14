#include "music_volume.h"

Music_volume::Music_volume( int vol )
{
	volume = vol;
	last_volume = 0;
}

Music_volume::~Music_volume()
{
	volume = 0;
	last_volume = 0;
	green_bar.free();
	white_bar.free();
	text.free();
}

	
void Music_volume::load( int screen_w, int screen_h, string str )
{
	white_bar.setAlpha( 255 );
	white_bar.create( 128*3, 40, 0xFF, 0xFF, 0xFF );
	white_bar.setPosition( screen_w/3 + white_bar.getWidth()/2, screen_h/2 - white_bar.getHeight()/2 );
	
	//green_bar.create( volume*3, 40 );
	text.setFont( "intro/Jaapokki-Regular.otf", 30, 0xFF, 0xFF, 0xFF  );
	text.setText( str );
}

void Music_volume::draw( sf::RenderWindow* &window )
{
	window->draw( white_bar.get() );
}

void Music_volume::handle( sf::Event &event )
{
	
	
}