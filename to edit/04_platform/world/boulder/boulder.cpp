#include "boulder.h"

Boulder_part::Boulder_part()
{
	free();
}

Boulder_part::~Boulder_part()
{
	free();
}

void Boulder_part::free()
{
	angle = 0;
	angle_vel = 0;
	vel = 0;
	hit = false;
	
	alpha = 0;
	state = 0;
	startX = 0;
	startY = 0;
	
	if( !blocks.empty() )
	{
		for( auto &i :blocks )
		{
			i->free();
		}
		
		blocks.clear();
	}
}

void Boulder_part::reset( int distance )
{
	angle = 0;
	hit = false;
	alpha = 0;
	state = 0;
	
	for( auto &i :blocks )
	{
		i->y = 0;
	}
	
	while( true )
	{
		if( distance > 0 )
		{
			moveX( 1 );
			distance --;
		}
		else
		{
			break;
		}
	}
}




void Boulder_part::addBlock( int n, int x, int y )
{
	blocks.push_back( new Block() ); 	// add block.
	blocks[ blocks.size()-1 ]->nr = n; 	// set chosen.
	blocks[ blocks.size()-1 ]->x = x; 	// set x.
	blocks[ blocks.size()-1 ]->y = y; 	// set y.
}

void Boulder_part::positioning( int width )
{
	addBlock( 0, 0, 0 );
	addBlock( 0, width*2, 0 );
	addBlock( 1, width +width/2, 0 );
}

void Boulder_part::setPosition( int x, int y, float vel, double angle_vel )
{
	this->startX = x +blocks[ 1 ]->x/2;
	this->startY = y;
	this->vel = vel;
	this->angle_vel = angle_vel;
	
	for( auto &i :blocks )
	{
		i->x += x;
	}
}

void Boulder_part::moveX( float vel )
{
	for( auto &it :blocks )
	{
		it->x += vel;
	}
	
	startX += vel;
}

void Boulder_part::moving( Rect* rect, int width )
{
	if( state == 0 )
	{
		if( rect->getX() +rect->getWidth() > startX &&
			rect->getY() +rect->getHeight() /2 < startY &&
			rect->getX() < startX +width )
		{
			state = 1;
		}
	}
	else if( state == 1 )
	{
		angle += angle_vel;
		blocks[ blocks.size() -1 ]->y += vel;
		if( blocks[ blocks.size() -1 ]->y >= startY -width/2 -width )
		{
			state = 2;
		}
	}
	else if( state == 2 )
	{
		if( alpha > 3 )
		{
			alpha -= 2;
		}
		else
		{
			state = 3;
		}
	}
}
	
	
	
unsigned Boulder_part::getSize()
{
	return blocks.size() -1;
}

float Boulder_part::getX( unsigned which )
{
	return blocks[ which ]->x;
}

float Boulder_part::getY( unsigned which )
{
	return blocks[ which ]->y;
}

int Boulder_part::getNr( unsigned which )
{
	return blocks[ which ]->nr;
}



bool Boulder_part::renderBoulder()
{
	if( state < 3 )
	{
		return true;
	}
	
	return false;
}

float Boulder_part::getBoulderX()
{
	return blocks[ blocks.size() -1 ]->x;
}

float Boulder_part::getBoulderY()
{
	return blocks[ blocks.size() -1 ]->y;
}

double Boulder_part::getBoulderAngle()
{
	return angle;
}

sf::Uint8 Boulder_part::getBoulderAlpha()
{
	return alpha;
}

void Boulder_part::setBoulderAlpha( sf::Uint8 a )
{
	alpha = a;
}




bool Boulder_part::harm( int width )
{
	if( blocks[ blocks.size()-1 ]->y >= startY -width*1.75 && !hit && state == 1 )
	{
		hit = true;
		return true;
	}
	
	return false;
}