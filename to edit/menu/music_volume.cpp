#include "music_volume.h"

Music_volume::Music_volume( sf::Uint8 vol )
{
	volume = vol;
	
}

Music_volume::~Music_volume()
{
	volume = 0;
	green_bar.free();
	white_bar.free();
	text.free();
}

	
void Music_volume::load( int screen_w, int screen_h )
{
	
}

void Music_volume::draw( sf::RenderWindow* &window )
{
	
}

void Music_volume::handle( sf::Event &event )
{
	
}