#include "click.h"


void Click::turn()
{
	play = !play;
}

void Click::setVolume( sf::Uint8 volume )
{
	click.setVolume( volume );
}