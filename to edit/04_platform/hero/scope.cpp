#include "scope.h"
 #include <stdio.h>

Scope::Scope()
{
	vel = 0;
	
	a = 0;
	b = 0;
}

Scope::~Scope()
{
	free();
}

void Scope::free()
{
	vel = 0;
	
	a = 0;
	b = 0;
}



void Scope::setVel( float vel )
{
	this->vel = vel;
}

float Scope::getVel()
{
	return vel;
}



void Scope::setFactor( int factor )
{
	b = factor;
}

void Scope::changeMind()
{
	// printf( "happen\n" );
	a = 0;
}

void Scope::move( int x, int screen_w )
{
	// printf( "%d %d\n", x, screen_w );
	if( a == 0 )
	{
		if( x > screen_w/2 )
			a = 1;
	}
	
	else if( a == 1 )
	{
		if( b == 2 )		a = 2;
		else if( b == 1 )	a = 0;
	}
	
	
	else if( a == 2 )
	{
		if( x < screen_w/2 )
			a = 3;
	}
	
	else if( a == 3 )
	{
		if( b == 2 )		a = 2;
		else if( b == 1 )	a = 0;
	}
	
	// printf( "%d\n", a );
}

int Scope::getState()
{
	// printf( "%d\n", a );
	return a;
}

void Scope::transform()
{
	if( a == 0 )
	{
		a = 1;
	}
	else if( a == 3 )
	{
		a = 2;
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

sf::Uint8 Scope::getFactor()
{
	return b;
}

bool Scope::allowMoving()
{
	if( a == 1 || a == 3 )
	{
		return true;
	}
		
	return false;
}

void Scope::reset()
{
	a = 0;
	b = 0;
}