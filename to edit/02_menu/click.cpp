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

void Click::turnOn()
{
	play = true;
}

void Click::turnOff()
{
	play = false;
}



bool Click::isPlayable()
{
	return play;
}

void Click::setVolume( sf::Uint8 volume )
{
	click.setVolume( volume );
}

void Click::setChunkName( std::string text )
{
	click.setID( text );
}

void Click::loadChunk( std::string text )
{
	click.load( text, 50 );
}

void Click::playChunk()
{
	click.play();
}