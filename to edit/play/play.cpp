#include "play/play.h"

Play::Play()
{
	
}

Play::~Play()
{
	
}

void Play::free()
{
	
}

	
void Play::load( int screen_width, int screen_height )
{
	
}


void Play::handle( sf::Event &event )
{
	
}

void Play::draw( sf::RenderWindow* &window )
{
	
}

	
bool Play::isQuit()
{
	if( state == 2 )
	{
		return true;
	}
	
	return false;
}

bool Play::backToMenu()
{
	if( state == 1 )
	{
		return true;
	}
	
	return false;
}
