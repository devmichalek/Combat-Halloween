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
	vel = 0;
	x = y = 0;
	startY = endY = 0;
	harmed = false;
	
	state = 0;
	alpha = 0;
}

void Spike::reset( int distance )
{
	x += distance;
	state = 0;
	alpha = 0;
	y = startY;
	harmed = false;
}



void Spike::setPosition( float x, float y, float endY )
{
	this->x = x;
	this->y = y;
	this->startY = y;
	this->endY = endY;
}

void Spike::setVel( float vel )
{
	this->vel = vel;
}

void Spike::setAlpha( sf::Uint8 alpha )
{
	if( state < 2 )
	{
		this->alpha = alpha;
	}
}

void Spike::doFall()
{
	if( state == 0 )
	{
		state = 1;
	}
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

void Spike::mechanics()
{
	if( state == 1 )
	{
		y += vel;
		if( y >= endY )
		{
			state = 2;
		}
	}
	else if( state == 2 )
	{
		alpha --;
		if( alpha == 0 )
		{
			state = 3;
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

float Spike::getEndY()
{
	return endY;
}

sf::Uint8 Spike::getAlpha()
{
	return alpha;
}

bool Spike::isAlive()
{
	if( state != 3 )
	{
		return true;
	}
	
	return false;
}

bool Spike::ableToHarm()
{
	if( !harmed && state == 1 )
	{
		return true;
	}
	
	return false;
}

void Spike::setAsHarmed()
{
	harmed = true;
}