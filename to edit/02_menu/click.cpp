#include "click.h"

Click::Click()
{
	focus = false;
	play = true;
}

Click::~Click()
{
	focus = false;
	play = true;
	click.free();
}


void Click::turn()
{
	play = !play;
}

bool Click::isPlayable()
{
	return play;
}

void Click::setVolume( sf::Uint8 volume )
{
	click.setVolume( volume );
}