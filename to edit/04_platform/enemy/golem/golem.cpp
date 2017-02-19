#include "golem.h"
#include <stdio.h>

Golem::Golem()
{
	state = APPEAR -1;
	offset = 0;
	delay = 0;
	counter = 0;
	
	left = 0;
	right = 0;
	
	hp = 0;
	hp_state = 0;
	
	damage = 0;
	vel = 0;
	direction = 0;
	
	xScale = yScale = 0;
	
	attack = 0;
	attack_line = 0;
	attack_count = 0;
}

Golem::~Golem()
{
	free();
}

void Golem::free()
{
	state = APPEAR -1;
	offset = 0;
	delay = 0;
	counter = 0;
	if( !line.empty() )
	{
		line.clear();
	}
	
	left = 0;
	right = 0;
	
	hp = 0;
	hp_state = 0;
	
	damage = 0;
	vel = 0;
	direction = 0;
	
	xScale = yScale = 0;
	
	attack = 0;
	attack_line = 0;
	attack_count = 0;
	
	if( !x.empty() )
	{
		x.clear();
	}
	
	if( !x2.empty() )
	{
		x2.clear();
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

void Golem::reset( int distance )
{
	while( true )
	{
		if( distance > 0 )
		{
			for( auto &it :x )
			{
				it ++;
			}
			
			for( auto &it :x2 )
			{
				it ++;
			}
			
			left ++;
			right ++;
			
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
	direction = 0;
	hp = hp_state;
	attack = 0;
	attack_count = 0;
}




void Golem::setX( vector <float> x )
{
	this->x = x;
}

void Golem::setX2( vector <float> x2 )
{
	this->x2 = x2;
}

void Golem::setY( vector <float> y )
{
	this->y = y;
}

void Golem::setLine( vector <sf::Uint8> line )
{
	this->line = line;
}

void Golem::setWidth( vector <int> width )
{
	this->width = width;
}

void Golem::setHeight( vector <int> height )
{
	this->height = height;
}

void Golem::setVelocity( float vel )
{
	this->vel = vel;
}

void Golem::setDelay( sf::Uint8 delay )
{
	this->delay = delay;
}

void Golem::setDamage( sf::Uint8 damage )
{
	this->damage = damage;
}

void Golem::setHeartPoints( int hp )
{
	this->hp = hp;
	hp_state = hp;
}

void Golem::setBorders( int left, int right )
{
	this->left = left;
	this->right = right;
}

void Golem::setAttackLine( sf::Uint8 attack_line )
{
	attack = 0;
	this->attack_line = attack_line;
}

void Golem::setScale( float xScale, float yScale )
{
	this->xScale = xScale;
	this->yScale = yScale;
}

void Golem::setDead()
{
	offset = 0;
	state = DEAD;
}




float Golem::getX()
{
	if( direction == 2 || direction == 0 )
	{
		return x2[ state ];
	}
	
	return x[ state ];
}

float Golem::getY()
{
	return y[ state ];
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

float Golem::getRealHeight()
{
	return height[ 0 ];
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



int8_t Golem::getState()
{
	return state;
}

sf::Uint8 Golem::getOffset()
{
	if( offset >= line[ state ]*delay )
	{
		offset = 0;
	}
	
	return offset /delay;
}

sf::Uint8 Golem::getDamage()
{
	return damage;
}

float Golem::getHorizontalScale()
{
	return xScale;
}

float Golem::getVerticalScale()
{
	return yScale;
}

int Golem::getHeartPoints()
{
	if( hp < 0 )
	{
		return 0;
	}

	return hp;
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

void Golem::moveX( int vel )
{
	for( auto &it :x )
	{
		it += vel;
	}
	
	for( auto &it :x2 )
	{
		it += vel;
	}
	
	left += vel;
	right += vel;
}

void Golem::harm( int damage )
{
	hp += damage;
}