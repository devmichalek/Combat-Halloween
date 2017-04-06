#include "slab.h"

Slab::Slab()
{
	flag = true;
}

Slab::~Slab()
{
	free();
}

void Slab::free()
{
	flag = true;
	click.free();
}



void Slab::turn()
{
	flag = !flag;
}

void Slab::turnOn()
{
	flag = true;
}

void Slab::turnOff()
{
	flag = false;
}



bool Slab::isPlayable()
{
	return flag;
}

void Slab::setVolume( sf::Uint8 volume )
{
	click.setVolume( volume );
}

void Slab::setName( std::string text )
{
	click.setID( text );
}

void Slab::load( std::string text )
{
	click.load( text, 50 );
}

void Slab::play()
{
	click.play();
}