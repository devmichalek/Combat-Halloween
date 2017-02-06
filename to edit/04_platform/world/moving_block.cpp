#include "moving_block.h"
#include <stdio.h>
Moving_block::Moving_block()
{
	width = 0;
	startX = endX = 0;
	vel = 0;
	state = 0;
}

Moving_block::~Moving_block()
{
	free();
}

void Moving_block::free()
{
	if( !blocks.empty() )
	{
		for( auto &i :blocks )
		{
			i->free();
		}
		
		blocks.clear();
	}
	
	width = 0;
	startX = endX = 0;
	vel = 0;
	state = 0;
}

void Moving_block::positioning()
{
	width = 128;
	
	blocks.push_back( new Block() );
	blocks[ blocks.size() -1 ]->nr = 5;
	blocks[ blocks.size() -1 ]->x = 0;
	
	blocks.push_back( new Block() );
	blocks[ blocks.size() -1 ]->nr = 7;
	blocks[ blocks.size() -1 ]->x = width;
}

void Moving_block::setPosition( int startX, int endX, int y, int vel )
{
	this->startX = startX;
	this->endX = endX;
	this->vel = vel;
	
	for( auto &i :blocks )
	{
		i->y = y;
		i->x += startX;
	}
	

}

void Moving_block::moveX( float vel )
{
	for( auto &it :blocks )
	{
		it->x += vel;
	}
	
	startX += vel;
	endX += vel;
}

void Moving_block::moving()
{
	if( state == 0 )
	{
		if( blocks[ 0 ]->x <= startX )
		{
			state = 1;
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
		}
		else
		{
			for( auto &i :blocks )
			{
				i->x += vel;
			}
		}
	}
	
	printf( "%d %d\n", startX, endX );
}


unsigned Moving_block::getSize()
{
	return blocks.size();
}

int Moving_block::getX( unsigned which )
{
	return blocks[ which ]->x;
}

int Moving_block::getY( unsigned which )
{
	return blocks[ which ]->y;
}

int Moving_block::getNr( unsigned which )
{
	return blocks[ which ]->nr;
}
