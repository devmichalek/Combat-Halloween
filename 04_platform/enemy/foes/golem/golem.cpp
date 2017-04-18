#include "golem.h"
#include <stdio.h>	// NULL

void Golem::setDead()
{
	offset = 0;
	state = DEAD;
}

float Golem::getRealX()
{
	return x[ 0 ];
}

float Golem::getRealY()
{
	return y[ 0 ];
}

float Golem::getRealWidth()
{
	return width[ 0 ];
}

float Golem::getAttackX()
{
	if( direction == 2 || direction == 0 )
	{
		return x2[ ATTACK ] -getAttackWidth();
	}
	
	return x[ ATTACK ];
}

float Golem::getAttackY()
{
	return y[ ATTACK ] +height[ ATTACK ]/3;
}

int Golem::getAttackWidth()
{
	return width[ APPEAR ] *0.50;
}

int Golem::getAttackHeight()
{
	return height[ APPEAR ]/2;
}




bool Golem::isAlive()
{
	if( state > APPEAR -1 && state < DEAD +1 )
	{
		return true;
	}
	
	return false;
}

bool Golem::harmSomebody()
{
	if( state == ATTACK )
	{
		if( offset /delay == 3 && attack_count < 1 )
		{
			attack_count++;
			return true;
		}
	}
	
	return false;
}




void Golem::appear( Rect* rect )
{
	if( state == APPEAR -1 && rect != NULL )
	{
		if( rect->getX() > left && rect->getX() + rect->getWidth() < right )
		{
			direction = 0;
			
			if( xScale > 0 )
			{
				xScale = -xScale;
			}
				
			state = APPEAR;
		}
	}
}

void Golem::walk( Rect* rect )
{
	if( rect != NULL )
	{
		if( rect->getX() +rect->getWidth() > left &&
		rect->getX() < right &&
		rect->getY() +rect->getHeight() > y[ state ] && 
		rect->getY() < y[ state ] +height[ state ] &&
		state < ATTACK )
		{
			if( rect->getX() +rect->getWidth()/4 < x[ WALK ] && x[ WALK ] > left )
			{
				if( xScale < 0 )
				{
					xScale = -xScale;
				}
					
				direction = 1;
			}
			else if( rect->getRight() -rect->getWidth()/4 > x2[ WALK ] && x[ WALK ] < right )
			{
				if( xScale > 0 )
				{
					xScale = -xScale;
				}
					
				direction = 2;
			}
			else
			{
				if( direction == 1 )		direction = 3;
				else if( direction == 2 )	direction = 0;
			}
		}
		else
		{
			if( direction == 1 )		direction = 3;
			else if( direction == 2 )	direction = 0;
		}
	}
}

void Golem::mechanics()
{
	if( state > APPEAR -1 && state < DEAD +1 )
	{
		offset ++;
		if( offset == line[ state ]*delay )
		{
			attack ++;
			attack_count = 0;
			state = WALK;	// reset
			offset = 0;
		}
			
		if( state == APPEAR )
		{
			if( offset == 0 )
			{
				state = WALK;
			}
		}
		else if( state == WALK )
		{
			if( direction == 0 || direction == 3 )
			{
				if( offset >= line[ state ]*delay )
				{
					offset = 0;
				}
			}
			else if( direction == 1 )
			{
				for( auto &it :x )
				{
					it -= vel;
				}
				
				for( auto &it :x2 )
				{
					it -= vel;
				}
			}
			else if( direction == 2 )
			{
				for( auto &it :x )
				{
					it += vel;
				}
				
				for( auto &it :x2 )
				{
					it += vel;
				}
			}
		}
		else if( state == DEAD )
		{
			if( offset == line[ state ]*delay -1 )
			{
				state = DEAD +1;
			}
		}
	}
}

void Golem::ableAttack()
{
	if( state < ATTACK && attack >= attack_line )
	{
		attack = 0;
		offset = 0;
		state = ATTACK;
	}
}