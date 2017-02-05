#include "wallblock.h"

WallBlock::WallBlock()
{
	width = 0;
	
	vel = 0;
	startY = 0;
	state = 0;
	surplus = 0;
	hit = false;
}

WallBlock::~WallBlock()
{
	free();
}

void WallBlock::free()
{
	width = 0;
	
	if( !blocks.empty() )
	{
		for( auto &i :blocks )
		{
			i->free();
		}
		
		blocks.clear();
	}
	
	vel = 0;
	startY = 0;
	state = 0;
	surplus = 0;
	hit = false;
}



void WallBlock::positioning()
{
	width = 128;
	int length = 2;
	
	// First line of blocks.
	blocks.push_back( new Block() );
	blocks[ blocks.size()-1 ]->nr = 10;
	blocks[ blocks.size()-1 ]->y = -(width*(length+1));
	for( int i = 1; i < length; i++ )
	{
		blocks.push_back( new Block() );
		blocks[ blocks.size()-1 ]->nr = 10;
		blocks[ blocks.size()-1 ]->y = blocks[ blocks.size()-2 ]->y +width;
	}
	blocks.push_back( new Block() );
	blocks[ blocks.size()-1 ]->nr = 8;
	blocks[ blocks.size()-1 ]->y = -width;
	
	
	// Second line of blocks.
	blocks.push_back( new Block() );
	blocks[ blocks.size()-1 ]->nr = 12;
	blocks[ blocks.size()-1 ]->y = -(width*(length+1));
	blocks[ blocks.size()-1 ]->x = width;
	for( int i = 1; i < length; i++ )
	{
		blocks.push_back( new Block() );
		blocks[ blocks.size()-1 ]->nr = 12;
		blocks[ blocks.size()-1 ]->y = blocks[ blocks.size()-2 ]->y +width;
		blocks[ blocks.size()-1 ]->x = width;
	}
	blocks.push_back( new Block() );
	blocks[ blocks.size()-1 ]->nr = 9;
	blocks[ blocks.size()-1 ]->y = -width;
	blocks[ blocks.size()-1 ]->x = width;
}

void WallBlock::setPosition( int x, int y, int vel, int surplus )
{
	for( auto &i :blocks )
	{
		i->x += x;
		i->y += y;
	}
	
	startY = y;
	this->vel = vel;
	this->surplus = surplus;
}

void WallBlock::moveX( float vel )
{
	for( auto &it :blocks )
	{
		it->x += vel;
	}
}

void WallBlock::moving()
{
	if( state == 0 )
	{
		if( blocks[ blocks.size()-1 ]->y <= startY -(width*2) -surplus )
		{
			state = 1;
		}
		else
		{
			for( auto &i :blocks )
			{
				i->y -= vel;
			}
		}
	}
	else
	{
		if( blocks[ blocks.size()-1 ]->y >= startY )
		{
			state = 0;
			hit = false;
		}
		else
		{
			for( auto &i :blocks )
			{
				i->y += vel*2;
			}
		}
	}
}
	
	
	
unsigned WallBlock::getSize()
{
	return blocks.size();
}

int WallBlock::getX( unsigned which )
{
	return blocks[ which ]->x;
}

int WallBlock::getY( unsigned which )
{
	return blocks[ which ]->y;
}

int WallBlock::getNr( unsigned which )
{
	return blocks[ which ]->nr;
}

int WallBlock::getMainX()
{
	return blocks[ 0 ]->x;
}

int WallBlock::getMainR()
{
	return blocks[ 0 ]->x +(width*2);
}

bool WallBlock::harm()
{
	if( blocks[ blocks.size()-1 ]->y >= startY -width/3 && !hit && state == 0 )
	{
		hit = true;
		return true;
	}
	
	return false;
}