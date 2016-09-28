#include "parentchunk.h"


void Parentchunk::turn()
{
	play = !play;
}

void Parentchunk::setVolume( sf::Uint8 volume )
{
	click.setVolume( volume );
}