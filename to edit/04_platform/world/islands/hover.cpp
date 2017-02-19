#include "hover.h"
#include <stdio.h>

Hover::Hover()
{
	startX = endX = 0;
	vel = 0;
	vel_state = 0;
	state = 0;
	awryS = false;
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
	
	startX = endX = 0;
	vel = 0;
	vel_state = 0;
	state = 0;
	awryS = false;
}



void Hover::positioning( int width, int type )
{
	blocks.push_back( new Block() );
	blocks[ blocks.size() -1 ]->nr = 5;
	blocks[ blocks.size() -1 ]->x = 0;
	
	if( type == 0 )
	{
		blocks.push_back( new Block() );
		blocks[ blocks.size() -1 ]->nr = 6;
		blocks[ blocks.size() -1 ]->x = width;
	}
	
	blocks.push_back( new Block() );
	blocks[ blocks.size() -1 ]->nr = 7;
	blocks[ blocks.size() -1 ]->x = blocks[ blocks.size() -2 ]->x +width;
}

void Hover::setPosition( int startX, int endX, int y, int vel )
{
	this->startX = startX;
	this->endX = endX;
	this->vel = vel;
	vel_state = vel;
	
	for( auto &i :blocks )
	{
		i->y = y;
		i->x += startX;
	}
	

}

void Hover::moveX( float vel )
{
	for( auto &it :blocks )
	{
		it->x += vel;
	}
	
	startX += vel;
	endX += vel;
}

void Hover::moving( int width )
{
	if( state == 0 )
	{
		if( blocks[ 0 ]->x <= startX )
		{
			state = 1;
			awryS = false;
		}
		else
		{
			for( auto &i :blocks )
			{
				i->x -= vel;
			}
		}
	}
	else
	{
		if( blocks[ blocks.size()-1 ]->x +width >= endX )
		{
			state = 0;
			awryS = false;
		}
		else
		{
			for( auto &i :blocks )
			{
				i->x += vel;
			}
		}
	}
}

void Hover::awry()
{
	if( !awryS )
	{
		// printf( "awry\n" );
		awryS = true;
		if( state = 0 )
		{
			state = 1;
		}
		else
		{
			state = 0;
		}
	}
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

int Hover::getX( unsigned which )
{
	return blocks[ which ]->x;
}

int Hover::getY( unsigned which )
{
	return blocks[ which ]->y;
}

int Hover::getNr( unsigned which )
{
	return blocks[ which ]->nr;
}
