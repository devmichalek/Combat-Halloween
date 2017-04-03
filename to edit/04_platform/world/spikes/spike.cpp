#include "spike.h"

Spike::Spike()
{
	free();
}

Spike::~Spike()
{
	free();
}

void Spike::free()
{
	x = y = 0;
	state = 0;
	line = 0;
	counter = 0;
	vel = 0;
}

void Spike::reset( int distance )
{
	x += distance;
	state = 0;
	counter = 0;
}



void Spike::setPosition( float x, float y )
{
	this->x = x;
	this->y = y;
}

void Spike::setLine( int line )
{
	this->line = line;
}

void Spike::setVel( float vel )
{
	this->vel = vel;
}



void Spike::moveX( sf::Uint8 direction, float vel )
{
	if( direction == 1 )
	{
		x += vel;
	}
	else if( direction == 2 )
	{
		x -= vel;
	}
}

void Spike::undoFall( sf::Uint8 add )
{
	x += add;
}



void Spike::mechanics( int screen_h, int width )
{
	if( state == 0 )
	{
		counter ++;
		if( counter >= line )
		{
			counter = 0;
			state = 1;
			if( vel < 0 )
			{
				y = screen_h;
			}
			else
			{
				y = -width;
			}
		}
	}
	else
	{
		y += vel;
		if( (vel < 0 && y < -width) ||
			(vel > 0 && y > screen_h) )
		{
			state = 0;
		}
	}
}

float Spike::getX()
{
	return x;
}

float Spike::getY()
{
	return y;
}

bool Spike::isAlive()
{
	if( state == 1 )
	{
		return true;
	}
	
	return false;
}