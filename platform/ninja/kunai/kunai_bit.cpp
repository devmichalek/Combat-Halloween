/**
    kunai_bit.h
    Purpose: class Kunai_bit contains position x,y particular shuriken, offset etc. stuff to draw.

    @author Adrian Michalek
    @version 2016.01.15
	@email adrmic98@gmail.com
*/

#include "kunai_bit.h"

Kunai_bit::Kunai_bit()
{
	free();
}

Kunai_bit::~Kunai_bit()
{
	free();
}

void Kunai_bit::free()
{
	x = y = 0;
	vel = 0;
	which = 0;
	active = false;
	
	offset = 0;
	line = 0;
	delay = 0;
}



float Kunai_bit::getX()
{
	return x;
}

float Kunai_bit::getY()
{
	return y;
}

float Kunai_bit::getVel()
{
	return vel;
}

int Kunai_bit::getWhich()
{
	return which;
}

bool Kunai_bit::isActive()
{
	return active;
}

sf::Uint8 Kunai_bit::getOffset()
{
	return offset /delay;
}



void Kunai_bit::setPosition( float sx, float sy, float vel, int which )
{
	if( !active )
	{
		x = sx;
		y = sy;
		this->vel = vel;
		this->which = which;
		active = true;
	}
}

void Kunai_bit::setAnimation( sf::Uint8 line, sf::Uint8 delay )
{
	this->line = line;
	this->delay = delay;
}



void Kunai_bit::run()
{
	if( active )
	{
		x += vel;
	}
	
	if( which == 3 )
	{
		offset ++;
		if( offset == line *delay )
		{
			offset = 0;
		}
	}
}

void Kunai_bit::moveX( float vel )
{
	x += vel;
}