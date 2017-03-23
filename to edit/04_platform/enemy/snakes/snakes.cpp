#include "snakes.h"
#include <stdio.h>

Snakes::Snakes()
{
	free();
}

Snakes::~Snakes()
{
	free();
}

void Snakes::free()
{
	state = APPEAR -1;
	offset = 0;
	delay = 0;
	counter = 0;
	if( !line.empty() )
	{
		line.clear();
	}
	
	hp = 0;
	hp_state = 0;
	
	damage = 0;
	
	xScale = yScale = 0;
	
	attack = 0;
	attack_line = 0;
	attack_count = 0;
	
	if( !x.empty() )
	{
		x.clear();
	}
	
	if( !y.empty() )
	{
		y.clear();
	}
	
	if( !width.empty() )
	{
		width.clear();
	}
	
	if( !height.empty() )
	{
		height.clear();
	}
}

void Snakes::reset( int distance )
{
	while( true )
	{
		if( distance > 0 )
		{
			for( auto &it :x )
			{
				it ++;
			}
			
			distance --;
		}
		else
		{
			break;
		}
	}
	
	state = APPEAR -1;
	offset = 0;
	counter = 0;
	hp = hp_state;
	attack = 0;
	attack_count = 0;
}




void Snakes::setX( vector <float> x )
{
	this->x = x;
}

void Snakes::setY( vector <float> y )
{
	this->y = y;
}

void Snakes::setLine( vector <sf::Uint8> line )
{
	this->line = line;
}

void Snakes::setWidth( vector <int> width )
{
	this->width = width;
}

void Snakes::setHeight( vector <int> height )
{
	this->height = height;
}

void Snakes::setDelay( sf::Uint8 delay )
{
	this->delay = delay;
}

void Snakes::setDamage( sf::Uint8 damage )
{
	this->damage = damage;
}

void Snakes::setHeartPoints( int hp )
{
	this->hp = hp;
	hp_state = hp;
}

void Snakes::setAttackLine( sf::Uint8 attack_line )
{
	attack = 0;
	this->attack_line = attack_line;
}

void Snakes::setScale( float xScale, float yScale )
{
	this->xScale = xScale;
	this->yScale = yScale;
}

void Snakes::setDead()
{
	offset = 0;
	state = DEAD;
}




float Snakes::getX()
{
	return x[ state ];
}

float Snakes::getY()
{
	return y[ state ];
}



float Snakes::getRealX()
{
	return x[ 0 ] +20*yScale;
}

float Snakes::getRealY()
{
	return y[ 0 ] -25*yScale;
}

float Snakes::getRealWidth()
{
	return width[ 1 ] -60*yScale;
}

float Snakes::getRealHeight()
{
	return height[ 0 ];
}



float Snakes::getAttackX()
{
	return x[ ATTACK ];
}

float Snakes::getAttackY()
{
	return y[ ATTACK ] +height[ ATTACK ]/3;
}

int Snakes::getAttackWidth()
{
	return width[ APPEAR ] *0.70;
}

int Snakes::getAttackHeight()
{
	return height[ APPEAR ]/2;
}



int8_t Snakes::getState()
{
	return state;
}

sf::Uint8 Snakes::getOffset()
{
	if( state == DEAD )
	{
		return offset /delay;
	}
	
	if( offset >= line[ state ]*delay )
	{
		offset = 0;
	}
	
	return offset /delay;
}

sf::Uint8 Snakes::getDamage()
{
	return damage;
}

float Snakes::getHorizontalScale()
{
	return xScale;
}

float Snakes::getVerticalScale()
{
	return yScale;
}

int Snakes::getHeartPoints()
{
	if( hp < 0 )
	{
		return 0;
	}

	return hp;
}

bool Snakes::isAlive()
{
	if( state > APPEAR -1 && state < DEAD +1 )
	{
		return true;
	}
	
	return false;
}

bool Snakes::harmSomebody()
{
	if( state == ATTACK )
	{
		if( offset /delay == 4 && attack_count < 1 )
		{
			attack_count++;
			return true;
		}
		else if( offset /delay == 7 && attack_count < 2 )
		{
			attack_count++;
			return true;
		}
	}
	
	return false;
}





void Snakes::appear( Rect* rect )
{
	if( state == APPEAR -1 && rect != NULL )
	{
		if( rect->getX() > x[ 0 ] && rect->getX() + rect->getWidth() < x[ 0 ] +width[ 0 ] )
		{
			if( xScale > 0 )
			{
				xScale = -xScale;
			}
				
			state = APPEAR;
		}
	}
}

void Snakes::mechanics()
{
	if( state > APPEAR -1 && state < DEAD +1 )
	{
		offset ++;
		if( offset == line[ state ]*delay )
		{
			attack ++;
			attack_count = 0;
			state = IDLE;	// reset
			offset = 0;
		}
			
		if( state == APPEAR )
		{
			if( offset == 0 )
			{
				state = IDLE;
			}
		}
		else if( state == IDLE )
		{
			state = IDLE;
			if( offset >= line[ state ]*delay )
			{
				offset = 0;
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

void Snakes::ableAttack()
{
	if( state < ATTACK && attack >= attack_line )
	{
		attack = 0;
		offset = 0;
		state = ATTACK;
	}
}

void Snakes::moveX( float vel )
{
	for( auto &it :x )
	{
		it += vel;
	}
}

void Snakes::harm( int damage )
{
	hp += damage;
}