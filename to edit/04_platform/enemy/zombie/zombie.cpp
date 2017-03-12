#include "zombie.h"

float Zombie::getRealX()
{
	return x[ 0 ] -15*yScale;
}

float Zombie::getRealY()
{
	return y[ 0 ];
}

float Zombie::getRealWidth()
{
	return width[ 1 ] +50*yScale;
}

bool Zombie::harmSomebody()
{
	if( state == ATTACK )
	{
		if( offset /delay == 4 && attack_count < 1 )
		{
			attack_count++;
			return true;
		}
	}
	
	return false;
}