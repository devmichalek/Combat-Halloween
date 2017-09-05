#include "zombie.h"

Zombie::Zombie()
{
	free();
}

Zombie::~Zombie()
{
	free();
}

void Zombie::free()
{
	if( !lines.empty() )
	{
		lines.clear();
	}
	
	armour = 0;
	damage = 0;
	velocity = 0;
	heartpoints = 0;
	heartpoints_state = 0;
	
	left = right = 0;
	x = y = 0;
	
	offset = 0;
	state = -1;
	appearwas = false;
	
	attack_line = 1;
	attack_counter = attack_line;
	attack_howmany = 0;
}



void Zombie::setLines( vector <sf::Uint8> lines )
{
	this->lines = lines;
}

void Zombie::setWidth( float width )
{
	this->width = width;
}

void Zombie::setScale( float scale_x, float scale_y )
{
	this->scale_x = scale_x;
	this->scale_y = scale_y;
}

void Zombie::setArmour( float value )
{
	this->armour = value;
}

void Zombie::setDamage( float value )
{
	this->damage = value;
}

void Zombie::setVelocity( float value )
{
	this->velocity = value;
}

void Zombie::setHP( float value )
{
	this->heartpoints = value;
	this->heartpoints_state = value;
}

void Zombie::harm( float value )
{
	heartpoints -= (value -(value *armour /1000));
	if( heartpoints <= 0 )
	{
		setDie();
	}
}

void Zombie::setLeft( float value )
{
	this->left = value;
}

void Zombie::setRight( float value )
{
	this->right = value;
}

void Zombie::setOffset( float value )
{
	this->offset = value;
}

void Zombie::setCenterX( float centerX )
{
	this->centerX = centerX;
}

void Zombie::setPosition( float x, float y )
{
	this->x = x;
	this->y = y;
}



void Zombie::moveX( double elapsedTime )
{
	if( attack_counter > attack_line /3 )
	{
		this->x += (elapsedTime *velocity);
	}
}

void Zombie::turnLeft()
{
	if( scale_x < 0 && attack_counter > attack_line /3 )
	{
		scale_x = -scale_x;
	}
}

void Zombie::turnRight()
{
	if( scale_x > 0 && attack_counter > attack_line /3 )
	{
		scale_x = -scale_x;
	}
}



void Zombie::setAppear()
{
	state = APPEAR;
	offset = 0;
}

void Zombie::setIdle()
{
	if( appearwas && state != ATTACK )
	{
		state = IDLE;
	}
}

void Zombie::setWalk()
{
	if( attack_counter > attack_line /3 )
	{
		state = WALK;
	}
}

void Zombie::setAttack()
{
	state = ATTACK;
	offset = 0;
	attack_counter = 0;
}

void Zombie::setDie()
{
	state = DIE;
	offset = 0;
}





int Zombie::getState()
{
	return state;
}

float Zombie::getOffset()
{
	return offset;
}


float Zombie::getLeft()
{
	return left;
}

float Zombie::getRight()
{
	return right;
}

float Zombie::getX()
{
	float xOffset = 0;
	
	if( scale_x < 0 )
	{
		if( state == APPEAR )		xOffset = width *0.87;
		else if( state == IDLE )	xOffset = width *0.59;
		else if( state == WALK )	xOffset = width *0.59;
		else if( state == ATTACK )	xOffset = width *1.01;
		else if( state == DIE )		xOffset = width *1.01;
	}
	else
	{
		if( state == ATTACK )	xOffset = -width *0.42;
		else if( state == DIE )	xOffset = -width *0.42;
	}
	
	return x +xOffset;
}

float Zombie::getY()
{
	return y;
}

float Zombie::getCenterX()
{
	return centerX;
}

float Zombie::getRealX()
{
	return x +(width *0.05);
}

float Zombie::getRealY()
{
	return y -getRealHeight();
}

float Zombie::getRealWidth()
{
	return width /2;
}

float Zombie::getRealHeight()
{
	return width *1.26;
}



float Zombie::getAttackX()
{
	float myx = getRealX() -getAttackWidth();
	
	if( scale_x < 0 )
	{
		myx += getAttackWidth() *2;
	}
	
	return myx;
}

float Zombie::getAttackY()
{
	return getRealY() +width *0.25;
}

float Zombie::getAttackWidth()
{
	return width *0.43;
}

float Zombie::getAttackHeight()
{
	return width *0.83;
}



bool Zombie::isAlive()
{
	if( state > -2 && state != DIE )
	{
		return true;
	}
	
	return false;
}

bool Zombie::ableToAppear()
{
	if( state == -1 )
	{
		return true;
	}
	
	return false;
}

bool Zombie::ableToWalk()
{
	if( state == IDLE || state == WALK )
	{
		return true;
	}
	
	return false;
}

bool Zombie::ableToAttack()
{
	if( (state == IDLE || state == WALK) && attack_counter > attack_line )
	{
		return true;
	}
	
	return false;
}

bool Zombie::isAttacking( bool hide )
{
	if( state == ATTACK )
	{
		if( static_cast <int> (offset) == 3 )
		{
			if( hide )
			{
				return true;
			}
			else if( attack_howmany == 0 )
			{
				attack_howmany ++;
				return true;
			}
		}
		else if( static_cast <int> (offset) == 6 )
		{
			if( hide )
			{
				return true;
			}
			else if( attack_howmany == 1 )
			{
				attack_howmany ++;
				return true;
			}
		}
	}
	
	return false;
}


float Zombie::getXScale()
{
	return scale_x;
}

float Zombie::getYScale()
{
	return scale_y;
}

float Zombie::getHPScale()
{
	if( heartpoints /heartpoints_state < 0 )
	{
		return 0;
	}
	
	return heartpoints /heartpoints_state;
}



float Zombie::getHP()
{
	return heartpoints;
}

float Zombie::getArmour()
{
	return armour;
}

float Zombie::getDamage()
{
	return damage;
}


void Zombie::mechanics( double elapsedTime )
{
	if( state > -1 )
	{
		offset += elapsedTime *20;
		
		if( state == APPEAR )
		{
			if( offset >= lines[ APPEAR ] )
			{
				offset = 0;
				appearwas = true;
				state = IDLE;
			}
		}
		
		if( state == IDLE )
		{
			if( offset >= lines[ IDLE ] )
			{
				offset = 0;
			}
		}
		
		if( state == WALK )
		{
			if( offset >= lines[ WALK ] )
			{
				offset = 0;
			}
		}
		
		if( state == ATTACK )
		{
			if( offset >= lines[ ATTACK ] )
			{
				attack_howmany = 0;
				offset = 0;
				state = IDLE;
			}
		}
		else
		{
			attack_counter += elapsedTime;
		}
		
		if( state == DIE )
		{
			if( offset >= lines[ DIE ] )
			{
				offset = 0;
				state = -2;
			}
		}
	}
}