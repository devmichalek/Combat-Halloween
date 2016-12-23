#include "hero/scope.h"
#include <stdio.h>

Scope::Scope()
{
	heroX = 0;
	left = right = 0;
	vel = 0;
	
	state = 0;
	screen_w = 0;
	width = 0;
}

Scope::~Scope()
{
	free();
}

void Scope::free()
{
	heroX = 0;
	left = right = 0;
	vel = 0;
	
	state = 0;
	screen_w = 0;
	width = 0;
}



void Scope::setHeroX( int x )
{
	heroX = x;
}

void Scope::setBorder( int left, int right )
{
	this->left = left;
	this->right = right;
}

void Scope::setVel( float vel )
{
	this->vel = vel;
}

void Scope::setWall( int width, int screen_w )
{
	this->width = width;
	this->screen_w = screen_w/2;
}



float Scope::getVel()
{
	return vel;
}


void Scope::move( sf::Uint8 direction )
{
	if( state == 0 )
	{
		if( direction == 1 )
		{
			heroX -= vel;
		}
		else if( direction == 2 )
		{
			heroX += vel;
		}
	}
	
	if( state == 1 )
	{
		if( direction == 1 ) // left
		{
			left += vel;
			right += vel;
			
		}
		else if( direction == 2 ) // right
		{
			left -= vel;
			right -= vel;
			
		}
	}
	
	vel = 0;
	
	//printf( "%d\n", state );
}


bool Scope::checkWall( int x )
{
	if( state == 0 )
	{
		if( x > screen_w/2 )
		{
			state = 1;
			return true;
		}
	}
	
	return false;
}


bool Scope::allowMoving()
{
	if( state == 1 )
	{
		return true;
	}
		
	return false;
}