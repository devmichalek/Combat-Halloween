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
	
	alpha_state = 0;
	alpha = 0xFF;
	
	hp = 0;
	hp_state = 0;
	
	xScale = yScale = 0;
	
	attack = 0;
	attack_line = 0;
	attack_count = 0;
	
	left = 0;
	
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
			
			left ++;
			
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
	alpha_state = 0;
	alpha = 0xFF;
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

void Snakes::setLeft( float x )
{
	left = x;
}

void Snakes::setDead()
{
	offset = 0;
	state = DEAD;
}

void Snakes::setAlphaState( sf::Uint8 s )
{
	alpha_state = s;
}

void Snakes::setAlpha( sf::Uint8 a )
{
	alpha = a;
}



float Snakes::getX()
{
	if( state == DEAD )
	{
		return x[ IDLE ];
	}
	
	return x[ state ];
}

float Snakes::getY()
{
	if( state == DEAD )
	{
		return y[ IDLE ];
	}
	
	return y[ state ];
}



float Snakes::getRealX()
{
	return x[ 0 ];
}

float Snakes::getRealY()
{
	return y[ 0 ];
}

float Snakes::getRealWidth()
{
	return width[ 0 ];
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
	return y[ ATTACK ];
}

int Snakes::getAttackWidth()
{
	return width[ APPEAR ] *0.5;
}

int Snakes::getAttackHeight()
{
	return height[ APPEAR ]/2;
}

int Snakes::getPlane()
{
	return y[ 0 ] +height[ 0 ];
}

sf::Uint8 Snakes::getAlpha()
{
	return alpha;
}

bool Snakes::alphaAble()
{
	if( alpha_state == 0 )
	{
		return true;
	}
	
	return false;
}



int8_t Snakes::getState()
{
	if( state == DEAD )
	{
		return IDLE;
	}
	
	return state;
}

sf::Uint8 Snakes::getOffset()
{
	if( state == DEAD )
	{
		if( offset >= line[ IDLE ]*delay )
		{
			offset = 0;
		}
	}
	else if( offset >= line[ state ]*delay )
	{
		offset = 0;
	}
	
	return offset /delay;
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
	if( state >= APPEAR && state <= DEAD )
	{
		return true;
	}
	
	return false;
}

bool Snakes::harmSomebody()
{
	if( state == ATTACK )
	{
		if( offset /delay == 1 && attack_count < 1 )
		{
			attack_count++;
			return true;
		}
	}
	
	return false;
}





void Snakes::appear( float x )
{
	if( state == APPEAR -1 )
	{
		if( x >= left )
		{
			state = APPEAR;
		}
	}
}

void Snakes::mechanics()
{
	if( state >= APPEAR && state <= DEAD )
	{
		offset ++;
		
		int8_t s;
		if( state != DEAD )	s = state;
		else				s = IDLE;
		
		if( offset == line[ s ]*delay )
		{
			attack ++;
			attack_count = 0;
			state = IDLE;	// reset
			offset = 0;
		}
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
		if( offset >= line[ state ]*delay )
		{
			offset = 0;
		}
	}
	else if( state == DEAD )
	{
		if( alpha > 5 )
			alpha -= 4;
		if( offset == line[ IDLE ]*delay -1 )
		{
			state = DEAD +1;
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
	left += vel;
	
	for( auto &it :x )
	{
		it += vel;
	}
}

void Snakes::harm( int damage )
{
	hp += damage;
}