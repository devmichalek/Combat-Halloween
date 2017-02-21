#include "vampire.h"
#include <stdio.h>

Vampire::Vampire()
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

Vampire::~Vampire()
{
	free();
}

void Vampire::free()
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

void Vampire::reset( int distance )
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




void Vampire::setX( vector <float> x )
{
	this->x = x;
}

void Vampire::setX2( vector <float> x2 )
{
	this->x2 = x2;
}

void Vampire::setY( vector <float> y )
{
	this->y = y;
}

void Vampire::setLine( vector <sf::Uint8> line )
{
	this->line = line;
}

void Vampire::setWidth( vector <int> width )
{
	this->width = width;
}

void Vampire::setHeight( vector <int> height )
{
	this->height = height;
}

void Vampire::setVelocity( float vel )
{
	this->vel = vel;
}

void Vampire::setDelay( sf::Uint8 delay )
{
	this->delay = delay;
}

void Vampire::setDamage( sf::Uint8 damage )
{
	this->damage = damage;
}

void Vampire::setHeartPoints( int hp )
{
	this->hp = hp;
	hp_state = hp;
}

void Vampire::setBorders( int left, int right )
{
	this->left = left;
	this->right = right;
}

void Vampire::setAttackLine( sf::Uint8 attack_line )
{
	attack = 0;
	this->attack_line = attack_line;
}

void Vampire::setScale( float xScale, float yScale )
{
	this->xScale = xScale;
	this->yScale = yScale;
}

void Vampire::setDead()
{
	offset = 0;
	state = DEAD;
}




float Vampire::getX()
{
	int result = state;
	if( result == DEAD )
	{
		result = APPEAR;
	}
	
	if( direction == 2 || direction == 0 )
	{
		return x2[ result ];
	}
	
	return x[ result ];
}

float Vampire::getY()
{
	int result = state;
	if( result == DEAD )
	{
		result = APPEAR;
	}
	
	return y[ result ];
}



float Vampire::getRealX()
{
	return x[ 0 ];
}

float Vampire::getRealY()
{
	return y[ 0 ];
}

float Vampire::getRealWidth()
{
	return width[ 0 ];
}

float Vampire::getRealHeight()
{
	return height[ 0 ];
}



float Vampire::getAttackX()
{
	if( direction == 2 || direction == 0 )
	{
		return x2[ ATTACK ] -getAttackWidth();
	}
	
	return x[ ATTACK ];
}

float Vampire::getAttackY()
{
	return y[ ATTACK ] +height[ ATTACK ]/3;
}

int Vampire::getAttackWidth()
{
	return width[ ATTACK ] *0.75;
}

int Vampire::getAttackHeight()
{
	return height[ APPEAR ]/2;
}



int8_t Vampire::getState()
{
	int result = state;
	if( result == DEAD )
	{
		result = APPEAR;
	}
	
	return result;
}

sf::Uint8 Vampire::getOffset()
{
	int result = state;
	if( result == DEAD )
	{
		result = APPEAR;
	}
	
	if( result != APPEAR )
	{
		if( offset >= line[ result ]*delay )
		{
			offset = 0;
		}
	}
	
	return offset /delay;
}

sf::Uint8 Vampire::getDamage()
{
	return damage;
}

float Vampire::getHorizontalScale()
{
	return xScale;
}

float Vampire::getVerticalScale()
{
	return yScale;
}

int Vampire::getHeartPoints()
{
	if( hp < 0 )
	{
		return 0;
	}

	return hp;
}

bool Vampire::isAlive()
{
	if( state > APPEAR -1 && state < DEAD +1 )
	{
		return true;
	}
	
	return false;
}

bool Vampire::harmSomebody()
{
	if( state == ATTACK )
	{
		if( offset /delay == 7 && attack_count < 1 )
		{
			attack_count++;
			return true;
		}
	}
	
	return false;
}





void Vampire::appear( Rect* rect )
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
			offset = line[ APPEAR ] *delay -1;
		}
	}
}

void Vampire::walk( Rect* rect )
{
	if( rect != NULL && state == WALK )
	{
		if( rect->getX() +rect->getWidth() > left &&
		rect->getX() < right &&
		rect->getY() +rect->getHeight() > y[ state ] && 
		rect->getY() < y[ state ] +height[ state ] )
		{
			if( rect->getRight() < x[ WALK ] && x[ WALK ] > left )
			{
				if( xScale < 0 )
				{
					xScale = -xScale;
				}
					
				direction = 1;
			}
			else if( rect->getX() > x2[ WALK ] && x[ WALK ] < right )
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

void Vampire::mechanics()
{
	if( state == APPEAR )
	{
		offset --;
		if( offset == 0 )
		{
			state = WALK;
			offset = 0;
		}
	}
	
	if( state == WALK || state == ATTACK )
	{
		offset ++;
		if( offset == line[ state ]*delay )
		{
			attack ++;
			attack_count = 0;
			state = WALK;	// reset
			offset = 0;
		}
			
		if( state == WALK )
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
	}
	
	if( state == DEAD )
	{
		offset ++;
		if( offset == line[ APPEAR ]*delay -1 )
		{
			offset = 0;
			state = DEAD +1;
		}
	}
}

void Vampire::ableAttack()
{
	if( state == WALK && attack >= attack_line )
	{
		attack = 0;
		offset = 0;
		state = ATTACK;
	}
}

void Vampire::moveX( int vel )
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

void Vampire::harm( int damage )
{
	hp += damage;
}