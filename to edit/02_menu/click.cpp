/**
    click.h
    Purpose: class Click - to play click.wav with state called focus for buttons.

    @author Adrian Michalek
    @version 2016.10.14
	@email adrmic98@gmail.com
*/

#include "click.h"

Click::Click()
{
	focus = false;
	play = true;
}

Click::~Click()
{
	free();
}

void Click::free()
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