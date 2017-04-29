#include "hover.h"
#include <stdio.h>

Hover::Hover()
{
	free();
}

Hover::~Hover()
{
	free();
}

void Hover::free()
{
	if( !blocks.empty() )
	{
		for( auto &i :blocks )
		{
			i->free();
		}
		
		blocks.clear();
	}

	vel = 0;
	vel_state = 0;
	state = false;
	stand = false;
	
	startX = 0;
	endX = 0;
}



void Hover::positioning( int width, int type )
{
	blocks.push_back( new Block() );
	blocks[ blocks.size() -1 ]->nr = 3;
	blocks[ blocks.size() -1 ]->x = 0;
	
	if( type == 0 )
	{
		blocks.push_back( new Block() );
		blocks[ blocks.size() -1 ]->nr = 4;
		blocks[ blocks.size() -1 ]->x = width;
	}
	
	blocks.push_back( new Block() );
	blocks[ blocks.size() -1 ]->nr = 5;
	blocks[ blocks.size() -1 ]->x = blocks[ blocks.size() -2 ]->x +width;
}

void Hover::setPosition( float startX, float endX, float y, float vel )
{
	this->vel = vel;
	vel_state = vel;
	
	this->startX = startX;
	this->endX = endX;
	
	for( auto &i :blocks )
	{
		i->y = y;
		i->x += startX;
	}
}

void Hover::moveX( float vel )
{
	if( !stand )
	{
		for( auto &it :blocks )
		{
			it->x += vel;
		}
	}
	
	startX += vel;
	endX += vel;
}

void Hover::moveX_stand( float vel )
{
	if( stand )
	{
		for( auto &it :blocks )
		{
			it->x += vel;
		}
	}
}

bool Hover::mechanics( int width )
{
	if( !stand )
	{
		if( state )
		{
			for( auto &i :blocks )
			{
				i->x -= vel;
			}
		}
		else
		{
			for( auto &i :blocks )
			{
				i->x += vel;
			}
		}
	}
	
	if( blocks[ 0 ]->x < startX || blocks[ blocks.size() -1 ]->x +width > endX )
	{
		state = !state;
		return true;
	}
	
	return false;
}


void Hover::turnOff()
{
	vel = 0;
}

void Hover::turnOn()
{
	vel = vel_state;
}


unsigned Hover::getSize()
{
	return blocks.size();
}

float Hover::getMainX()
{
	return blocks[ 0 ]->x;
}

float Hover::getMainY()
{
	return blocks[ 0 ]->y;
}

float Hover::getX( unsigned which )
{
	return blocks[ which ]->x;
}

float Hover::getY( unsigned which )
{
	return blocks[ which ]->y;
}

float Hover::getNr( unsigned which )
{
	return blocks[ which ]->nr;
}



void Hover::setStand( bool s )
{
	stand = s;
}

bool Hover::isStand()
{
	return stand;
}

float Hover::getVel()
{
	return vel;
}

sf::Uint8 Hover::getDirection()
{
	// right
	if( state )
	{
		return 1;
	}
	
	// left
	return 2;
}