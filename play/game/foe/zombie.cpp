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
	armour = 0;
	damage = 0;
	velocity = 0;
	heartpoints = 0;
	heartpoints_state = 0;
	
	x = y = 0;
	width = 0;
	centerX = 0;
	left = right = 0;
	scale = 0;
	
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

void Zombie::setHeartpoints( float value )
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

float Zombie::getArmour()
{
	return armour;
}

float Zombie::getDamage()
{
	return damage;
}

float Zombie::getVelocity()
{
	return velocity;
}

float Zombie::getHeartpoints()
{
	return heartpoints;
}

float Zombie::getHPScale()
{
	if( heartpoints /heartpoints_state < 0 )
	{
		return 0;
	}
	
	return heartpoints /heartpoints_state;
}




void Zombie::moveX( double elapsedTime )
{
	if( attack_counter > attack_line /3 )
	{
		this->x += (elapsedTime *velocity);
	}
}

void Zombie::setPosition( float x, float y )
{
	this->x = x;
	this->y = y;
}

void Zombie::setWidth( float width )
{
	this->width = width;
}

void Zombie::setCenterX( float centerX )
{
	this->centerX = centerX;
}

void Zombie::setBorders( float left, float right )
{
	this->left = left;
	this->right = right;
}

void Zombie::setScale( float scale )
{
	this->scale = scale;
}

void Zombie::turnLeft()
{
	if( scale < 0 && attack_counter > attack_line /3 )
	{
		scale = -scale;
	}
}

void Zombie::turnRight()
{
	if( scale > 0 && attack_counter > attack_line /3 )
	{
		scale = -scale;
	}
}

float Zombie::getX()
{
	float xOffset = 0;
	
	if( scale < 0 )
	{
		if( state == APPEAR )		xOffset = width *1.2121;
		else if( state == IDLE )	xOffset = width *1.12;
		else if( state == WALK )	xOffset = width *1.12;
		else if( state == ATTACK )	xOffset = width *1.58;
		else if( state == DIE )		xOffset = width *1.21;
	}
	else
	{
		if( state == ATTACK )	xOffset = -width *0.47;
		else if( state == DIE )	xOffset = -width *0.21;
	}
	
	return x +xOffset;
}

float Zombie::getY()
{
	float yOffset = width *0.01;
	if( state == ATTACK )
	{
		yOffset += width *0.032;
	}
		
	
	return y +yOffset;
}

float Zombie::getRealX()
{
	return x +(width *0.22);
}

float Zombie::getRealY()
{
	return y -getRealHeight();
}

float Zombie::getRealWidth()
{
	return width /1.5;
}

float Zombie::getRealHeight()
{
	return width *1.26;
}

float Zombie::getAttackX()
{
	float myx = getRealX() -getAttackWidth();
	
	if( scale < 0 )
	{
		myx += getRealX() +getRealWidth();
	}
	
	return myx;
}

float Zombie::getAttackY()
{
	return getRealY() +width *0.5;
}

float Zombie::getAttackWidth()
{
	return width *0.5;
}

float Zombie::getAttackHeight()
{
	return width *0.6;
}

float Zombie::getMouthX()
{
	return getRealX() +getRealWidth()/1.5;
}

float Zombie::getMouthY()
{
	return getRealY() +width *0.37;
}

float Zombie::getCenterX()
{
	return centerX;
}

float Zombie::getLeft()
{
	return left;
}

float Zombie::getRight()
{
	return right;
}

float Zombie::getScaleX()
{
	return scale;
}

float Zombie::getScaleY()
{
	float newScale = scale;
	if( newScale < 0 )	newScale = -newScale;
	
	return newScale;
}




void Zombie::setState( int value )
{
	this->state = value;
}

void Zombie::setOffset( float value )
{
	this->offset = value;
}

void Zombie::setLines( vector <sf::Uint8> lines )
{
	this->lines = lines;
}

int Zombie::getState()
{
	return state;
}

float Zombie::getOffset()
{
	return offset;
}

vector <sf::Uint8> Zombie::getLines()
{
	return lines;
}




void Zombie::setAppear()
{
	state = APPEAR;
	offset = 0;
	inactivity_counter = 0;
	inactivity_x = -1;
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
		inactivity_counter = 0;
		inactivity_x = -1;
	}
}

void Zombie::setAttack()
{
	state = ATTACK;
	offset = 0;
	attack_counter = 0;
	inactivity_counter = 0;
	inactivity_x = -1;
}

void Zombie::setDie()
{
	state = DIE;
	offset = 0;
	inactivity_counter = 0;
	inactivity_x = -1;
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
			else if( attacks == 0 )
			{
				attacks ++;
				return true;
			}
		}
		else if( static_cast <int> (offset) == 4 )
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

void Zombie::mechanics( double elapsedTime )
{
	if( state > -1 )
	{
		offset += elapsedTime *18;	// 18 offsets per second.
		
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




void Zombie::addText( string line )
{
	this->texts.push_back( line );
	chosen_text = rand() %texts.size();
}

bool Zombie::showText()
{
	if( text_counter > text_line && state != DIE )
	{
		return true;
	}
	
	return false;
}

string Zombie::getText()
{
	return texts[ chosen_text ];
}

bool Zombie::isLeftText()
{
	if( scale < 0 )
	{
		return false;
	}
	
	return true;
}