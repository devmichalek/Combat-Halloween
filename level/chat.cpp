#include "chat.h"

Chat::Chat()
{
	free();
}

Chat::~Chat()
{
	free();
}

void Chat::free()
{
	screen_w = 0;
	screen_h = 0;
	
	// Background.
	background.free();
	
	// Chunk.
	click.free();
}

void Chat::load( float screen_w, float screen_h )
{
	
}

void Chat::handle( sf::Event& event )
{
	
}

void Chat::draw( sf::RenderWindow* &window )
{
	
}


void Chat::setPlayable( bool playable )
{
	
}

void Chat::setVolume( float volume )
{
	
}
