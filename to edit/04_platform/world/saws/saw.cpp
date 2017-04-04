#include "saw.h"

void Saw::free()
{
	vel = 0;
	x = y = 0;
	endY = 0;
	harmed = false;
	
	state = 0;
	alpha = 0;
}

void Saw::mechanics()
{
	if( state == 1 )
	{
		angle += 5;
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

double Saw::getAngle()
{
	return angle;
}