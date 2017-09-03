#include "skeleton.h"

Skeleton::Skeleton()
{
	free();
}

Skeleton::~Skeleton()
{
	free();
}

void Skeleton::free()
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
}



void Skeleton::setLines( vector <sf::Uint8> lines )
{
	this->lines = lines;
}

void Skeleton::setWidth( float width )
{
	this->width = width;
}

void Skeleton::setScale( float scale_x, float scale_y )
{
	this->scale_x = scale_x;
	this->scale_y = scale_y;
}

void Skeleton::setArmour( float value )
{
	this->armour = value;
}

void Skeleton::setDamage( float value )
{
	this->damage = value;
}

void Skeleton::setVelocity( float value )
{
	this->velocity = value;
}

void Skeleton::setHP( float value )
{
	this->heartpoints = value;
	this->heartpoints_state = value;
}

void Skeleton::harm( float value )
{
	heartpoints -= (value -(value *armour /1000));
	if( heartpoints <= 0 )
	{
		setDie();
	}
}

void Skeleton::setLeft( float value )
{
	this->left = value;
}

void Skeleton::setRight( float value )
{
	this->right = value;
}

void Skeleton::setOffset( float value )
{
	this->offset = value;
}

void Skeleton::setCenterX( float centerX )
{
	this->centerX = centerX;
}

void Skeleton::setPosition( float x, float y )
{
	this->x = x;
	this->y = y;
}



void Skeleton::moveX( double elapsedTime )
{
	if( attack_counter > attack_line /3 )
	{
		this->x += (elapsedTime *velocity);
	}
}

void Skeleton::turnLeft()
{
	if( scale_x < 0 && attack_counter > attack_line /3 )
	{
		scale_x = -scale_x;
	}
}

void Skeleton::turnRight()
{
	if( scale_x > 0 && attack_counter > attack_line /3 )
	{
		scale_x = -scale_x;
	}
}



void Skeleton::setAppear()
{
	state = APPEAR;
	offset = 0;
}

void Skeleton::setIdle()
{
	if( appearwas && state != ATTACK )
	{
		state = IDLE;
	}
}

void Skeleton::setWalk()
{
	if( attack_counter > attack_line /3 )
	{
		state = WALK;
	}
}

void Skeleton::setAttack()
{
	state = ATTACK;
	offset = 0;
}

void Skeleton::setDie()
{
	state = DIE;
	offset = 0;
}





int Skeleton::getState()
{
	return state;
}

float Skeleton::getOffset()
{
	return offset;
}


float Skeleton::getLeft()
{
	return left;
}

float Skeleton::getRight()
{
	return right;
}

float Skeleton::getX()
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

float Skeleton::getY()
{
	float yOffset = 0;
	if( state == ATTACK )	yOffset = width *0.073;
	
	return y +yOffset;
}

float Skeleton::getCenterX()
{
	return centerX;
}

float Skeleton::getRealX()
{
	return x +(width *0.05);
}

float Skeleton::getRealY()
{
	return y -getRealHeight();
}

float Skeleton::getRealWidth()
{
	return width /2;
}

float Skeleton::getRealHeight()
{
	return width *1.26;
}



bool Skeleton::isAlive()
{
	if( state > -2 && state != DIE )
	{
		return true;
	}
	
	return false;
}

bool Skeleton::ableToAppear()
{
	if( state == -1 )
	{
		return true;
	}
	
	return false;
}

bool Skeleton::ableToWalk()
{
	if( state == IDLE || state == WALK )
	{
		return true;
	}
	
	return false;
}

bool Skeleton::ableToAttack()
{
	if( (state == IDLE || state == WALK) && attack_counter > attack_line )
	{
		return true;
	}
	
	return false;
}


float Skeleton::getXScale()
{
	return scale_x;
}

float Skeleton::getYScale()
{
	return scale_y;
}

float Skeleton::getHPScale()
{
	if( heartpoints /heartpoints_state < 0 )
	{
		return 0;
	}
	
	return heartpoints /heartpoints_state;
}



float Skeleton::getHP()
{
	return heartpoints;
}

float Skeleton::getArmour()
{
	return armour;
}


void Skeleton::mechanics( double elapsedTime )
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
				offset = 0;
				state = IDLE;
				attack_counter = 0;
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