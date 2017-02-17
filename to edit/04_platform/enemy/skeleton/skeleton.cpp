#include "skeleton.h"
#include <stdio.h>

Skeleton::Skeleton()
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
	flag = false;
}

Skeleton::~Skeleton()
{
	free();
}

void Skeleton::free()
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
	
	flag = false;
}

void Skeleton::reset( int distance )
{
	while( true )
	{
		if( distance > 0 )
		{
			for( auto &it :x )
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
	
	flag = false;
}




void Skeleton::setX( vector <float> x )
{
	this->x = x;
}

void Skeleton::setY( vector <float> y )
{
	this->y = y;
}

void Skeleton::setLine( vector <sf::Uint8> line )
{
	this->line = line;
}

void Skeleton::setWidth( vector <int> width )
{
	this->width = width;
}

void Skeleton::setHeight( vector <int> height )
{
	this->height = height;
}

void Skeleton::setVelocity( float vel )
{
	this->vel = vel;
}

void Skeleton::setDelay( sf::Uint8 delay )
{
	this->delay = delay;
}

void Skeleton::setDamage( sf::Uint8 damage )
{
	this->damage = damage;
}

void Skeleton::setHeartPoints( int hp )
{
	this->hp = hp;
	hp_state = hp;
}

void Skeleton::setBorders( int left, int right )
{
	this->left = left;
	this->right = right;
}

void Skeleton::setAttackLine( sf::Uint8 attack_line )
{
	attack = 0;
	this->attack_line = attack_line;
}

void Skeleton::setScale( float xScale, float yScale )
{
	this->xScale = xScale;
	this->yScale = yScale;
}

void Skeleton::setDead()
{
	offset = 0;
	state = DEAD;
}




float Skeleton::getX()
{
	if( (direction == 2 || direction == 0) && flag )
	{
		if( state < ATTACK )
		{
			return x[ state ] +width[ APPEAR ]/2;
		}
		else
		{
			return x[ state ] +width[ APPEAR ] +(30*yScale);
		}
		
	}
	else if( state == ATTACK )
	{
		return x[ state ] -(60*yScale);
	}
	
	
	return x[ state ];
}

float Skeleton::getY()
{
	return y[ state ];
}



float Skeleton::getRealX()
{
	return x[ 0 ];
}

float Skeleton::getRealY()
{
	return y[ 0 ];
}

float Skeleton::getRealWidth()
{
	return width[ 0 ];
}

float Skeleton::getRealHeight()
{
	return height[ 0 ];
}



float Skeleton::getAttackX()
{
	if( direction == 2 || direction == 0 )
	{
		return x[ ATTACK ] +194*yScale;
	}
	
	return x[ ATTACK ] -55*yScale;
}

float Skeleton::getAttackY()
{
	return y[ ATTACK ] +height[ ATTACK ]/3;
}

int Skeleton::getAttackWidth()
{
	return width[ APPEAR ]/3;
}

int Skeleton::getAttackHeight()
{
	return height[ APPEAR ]/2;
}



int8_t Skeleton::getState()
{
	return state;
}

sf::Uint8 Skeleton::getOffset()
{
	if( offset >= line[ state ]*delay )
	{
		offset = 0;
	}
	
	return offset /delay;
}

sf::Uint8 Skeleton::getDamage()
{
	return damage;
}

float Skeleton::getHorizontalScale()
{
	return xScale;
}

float Skeleton::getVerticalScale()
{
	return yScale;
}

int Skeleton::getHeartPoints()
{
	if( hp < 0 )
		return 0;
		
	return hp;
}

bool Skeleton::isAlive()
{
	if( state > APPEAR -1 && state < DEAD +1 )
	{
		return true;
	}
	
	return false;
}

bool Skeleton::isSword()
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





void Skeleton::appear( Rect* rect )
{
	if( state == APPEAR -1 && rect != NULL )
	{
		if( rect->getX() > left && rect->getX() + rect->getWidth() < right )
		{
			// printf( "appeared\n" );
			state = APPEAR;
		}
	}
}

void Skeleton::walk( Rect* rect )
{
	if( rect != NULL )
	{
		if( rect->getX() +rect->getWidth() > left &&
		rect->getX() < right &&
		rect->getY() +rect->getHeight() > y[ state ] && 
		rect->getY() < y[ state ] +height[ state ] &&
		state < ATTACK )
		{
			if( rect->getX() +rect->getWidth()/2 -5 < x[ ATTACK ] && x[ WALK ] > left )
			{
				if( xScale < 0 )	xScale = -xScale;
				direction = 1;
			}
			else if( rect->getX() +rect->getWidth() > x[ WALK ] +width[ WALK ]/6 && x[ WALK ] < right )
			{
				if( xScale > 0 )	xScale = -xScale;
				direction = 2;
				flag = true;
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

void Skeleton::mechanics()
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
		else if( state == IDLE || state == WALK )
		{
			if( direction == 0 || direction == 3 )
			{
				if( offset >= line[ state ]*delay )
				{
					offset = 0;
				}
				
				state = IDLE;
			}
			else if( direction == 1 )
			{
				state = WALK;
				
				for( auto &it :x )
				{
					it -= vel;
				}
			}
			else if( direction == 2 )
			{
				state = WALK;
				
				for( auto &it :x )
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

void Skeleton::ableAttack()
{
	if( state < ATTACK && attack >= attack_line )
	{
		attack = 0;
		offset = 0;
		state = ATTACK;
	}
}

void Skeleton::moveX( int vel )
{
	for( auto &it :x )
	{
		it += vel;
	}
	
	left += vel;
	right += vel;
}

void Skeleton::harm( int damage )
{
	hp += damage;
}