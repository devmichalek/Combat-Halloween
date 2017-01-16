#include "scope.h"
#include <stdio.h>

Scope::Scope()
{
	x = 0;
	vel = 0;
	
	screen_w = 0;
	width = 0;
	
	a = 0;
	b = 0;
}

Scope::~Scope()
{
	free();
}

void Scope::free()
{
	x = 0;
	vel = 0;
	
	screen_w = 0;
	width = 0;
	
	a = 0;
	b = 0;
}



void Scope::set( int x, int width, int screen_w )
{
	this->x = x;
	this->width = width;
	this->screen_w = screen_w;
}


void Scope::setVel( float vel )
{
	this->vel = vel;
}

float Scope::getVel()
{
	return vel;
}

void Scope::setFactor( int b )
{
	this->b = b;
}

void Scope::move( sf::Uint8 direction )
{
	if( a == 0 )
	{
		if( direction == 1 )		x -= vel;
		else if( direction == 2 )	x += vel;
		
		if( x > screen_w/2 )	a = 1;
	}
	
	else if( a == 1 )
	{
		if( b == 2 )		a = 2;
		else if( b == 1 )	a = 0;
	}
	
	
	else if( a == 2 )
	{
		if( direction == 1 )		x -= vel;
		else if( direction == 2 )	x += vel;
		
		if( x < screen_w/2 )	a = 3;
	}
	
	else if( a == 3 )
	{
		if( b == 2 )		a = 2;
		else if( b == 1 )	a = 0;
	}
	
	vel = 0;
}

int Scope::getState()
{
	// printf( "%d\n", a );
	return a;
}

void Scope::setNewX( int distance )
{
	int component;
	if( distance < 0 )
		component = 1;
	else
		component = -1;
		
	while( true )
	{
		if( distance == 0 )
			break;
			
		distance += component;
		x += component;
	}
}

bool Scope::getScope()
{
	if( a == 0 || a == 2 )
	{
		return true;
	}
	
	return false;
}

bool Scope::allowMoving()
{
	if( a == 1 || a == 3 )
	{
		return true;
	}
		
	return false;
}