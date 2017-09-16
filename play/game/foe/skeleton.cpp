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
	armour = 0;
	damage = 0;
	velocity = 0;
	heartpoints = 0;
	heartpoints_state = 0;
	
	x = y = 0;
	width = 0;
	centerX = 0;
	left = right = 0;
	scale_x = scale_y = 0;
	
	state = -1;
	offset = 0;
	if( !lines.empty() )
	{
		lines.clear();
	}
	
	appearwas = false;
	attacks = 0;
	attack_line = 1;
	attack_counter = attack_line;
	
	inactivity_x = 0;
	inactivity_line = rand() %5 +3;	// 4 seconds.
	inactivity_counter = -1;
	
	
	chosen_text = 0;
	text_line = text_line = rand() %8 +8;;	// 8 seconds.
	text_counter = 0;
	if( !texts.empty() )
	{
		texts.clear();
		texts.shrink_to_fit();
	}
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

void Skeleton::setHeartpoints( float value )
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

float Skeleton::getArmour()
{
	return armour;
}

float Skeleton::getDamage()
{
	return damage;
}

float Skeleton::getVelocity()
{
	return velocity;
}

float Skeleton::getHeartpoints()
{
	return heartpoints;
}

float Skeleton::getHPScale()
{
	if( heartpoints /heartpoints_state < 0 )
	{
		return 0;
	}
	
	return heartpoints /heartpoints_state;
}




void Skeleton::moveX( double elapsedTime )
{
	if( attack_counter > attack_line /3 )
	{
		this->x += (elapsedTime *velocity);
	}
}

void Skeleton::setPosition( float x, float y )
{
	this->x = x;
	this->y = y;
}

void Skeleton::setWidth( float width )
{
	this->width = width;
}

void Skeleton::setCenterX( float centerX )
{
	this->centerX = centerX;
}

void Skeleton::setBorders( float left, float right )
{
	this->left = left;
	this->right = right;
}

void Skeleton::setScale( float scale_x, float scale_y )
{
	this->scale_x = scale_x;
	this->scale_y = scale_y;
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

float Skeleton::getAttackX()
{
	float myx = getRealX() -getAttackWidth();
	
	if( scale_x < 0 )
	{
		myx += getAttackWidth() *2;
	}
	
	return myx;
}

float Skeleton::getAttackY()
{
	return getRealY() +width *0.5;
}

float Skeleton::getAttackWidth()
{
	return width *0.43;
}

float Skeleton::getAttackHeight()
{
	return width *0.6;
}

float Skeleton::getMouthX()
{
	return getRealX() +getRealWidth()/1.5;
}

float Skeleton::getMouthY()
{
	return getRealY() +width *0.45;
}

float Skeleton::getCenterX()
{
	return centerX;
}

float Skeleton::getLeft()
{
	return left;
}

float Skeleton::getRight()
{
	return right;
}

float Skeleton::getXScale()
{
	return scale_x;
}

float Skeleton::getYScale()
{
	return scale_y;
}




void Skeleton::setState( int value )
{
	this->state = value;
}

void Skeleton::setOffset( float value )
{
	this->offset = value;
}

void Skeleton::setLines( vector <sf::Uint8> lines )
{
	this->lines = lines;
}

int Skeleton::getState()
{
	return state;
}

float Skeleton::getOffset()
{
	return offset;
}

vector <sf::Uint8> Skeleton::getLines()
{
	return lines;
}




void Skeleton::setAppear()
{
	state = APPEAR;
	offset = 0;
	inactivity_counter = 0;
	inactivity_x = -1;
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
		inactivity_counter = 0;
		inactivity_x = -1;
	}
}

void Skeleton::setAttack()
{
	state = ATTACK;
	offset = 0;
	attack_counter = 0;
	inactivity_counter = 0;
	inactivity_x = -1;
}

void Skeleton::setDie()
{
	state = DIE;
	offset = 0;
	inactivity_counter = 0;
	inactivity_x = -1;
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

bool Skeleton::isAttacking( bool hide )
{
	if( state == ATTACK )
	{
		if( static_cast <int> (offset) == 3 )
		{
			if( hide )
			{
				return true;
			}
			else if( attacks == 0 )
			{
				attacks ++;
				return true;
			}
		}
		else if( static_cast <int> (offset) == 6 )
		{
			if( hide )
			{
				return true;
			}
			else if( attacks == 1 )
			{
				attacks ++;
				return true;
			}
		}
	}
	
	return false;
}

void Skeleton::mechanics( double elapsedTime )
{
	if( state > -1 )
	{
		offset += elapsedTime *20;	// 20 offsets per second.
		
		if( state == APPEAR )
		{
			if( offset >= lines[ APPEAR ] )
			{
				offset = 0;
				appearwas = true;
				state = IDLE;
			}
		}
		
		if( inactivity_x != -1 )
		{
			if( getRealX() +getRealWidth() < inactivity_x )
			{
				state = WALK;
				turnRight();
				moveX( elapsedTime );
				if( getRealX() +getRealWidth() > inactivity_x )
				{
					inactivity_counter = 0;
					inactivity_x = -1;
					state = IDLE;
					offset = 0;
				}
			}
			else if( getRealX() > inactivity_x )
			{
				state = WALK;
				turnLeft();
				moveX( -elapsedTime );
				if( getRealX() < inactivity_x )
				{
					inactivity_counter = 0;
					inactivity_x = -1;
					state = IDLE;
					offset = 0;
				}
			}
		}
		
		if( state == IDLE )
		{
			if( offset >= lines[ IDLE ] )
			{
				offset = 0;
			}
			
			inactivity_counter += elapsedTime;
			if( inactivity_counter > inactivity_line )
			{
				inactivity_line = rand() %5 +3;
				inactivity_x = rand() %static_cast <int> (right -left) +left;
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
				attacks = 0;
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
		else if( texts.size() > 0 )
		{
			text_counter += elapsedTime;
			if( text_counter > text_line *1.5 )
			{
				text_counter = 0;
				text_line = rand() %8 +8;
				chosen_text = rand() %texts.size();
			}
		}
	}
}




void Skeleton::addText( wstring line )
{
	this->texts.push_back( line );
	chosen_text = rand() %texts.size();
}

bool Skeleton::showText()
{
	if( text_counter > text_line )
	{
		return true;
	}
	
	return false;
}

wstring Skeleton::getText()
{
	return texts[ chosen_text ];
}

bool Skeleton::isLeftText()
{
	if( scale_x < 0 )
	{
		return false;
	}
	
	return true;
}