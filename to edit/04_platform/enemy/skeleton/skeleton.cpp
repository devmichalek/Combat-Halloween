#include "skeleton.h"
#include <stdio.h>

Skeleton::Skeleton()
{
	state = 0;
	offset = 0;
	delay = 0;
	counter = 0;
	
	startX = 0;
	endX = 0;
	
	hp = 0;
	hp_state = 0;
	damage = 0;
	vel = 0;
	direction = 0;
	
	attack = 0;
	attack_line = 0;
}

Skeleton::~Skeleton()
{
	free();
}

void Skeleton::free()
{
	state = 0;
	offset = 0;
	delay = 0;
	counter = 0;
	
	if( !x.empty() )
	{
		x.clear();
	}
	
	if( !y.empty() )
	{
		y.clear();
	}
	
	if( !line.empty() )
	{
		line.clear();
	}
	
	if( !width.empty() )
	{
		width.clear();
	}
	
	startX = 0;
	endX = 0;
	
	hp = 0;
	hp_state = 0;
	damage = 0;
	vel = 0;
	direction = 0;
	
	attack = 0;
	attack_line = 0;
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
			
			for( auto &it :y )
			{
				it ++;
			}
			
			startX ++;
			endX ++;
			
			distance --;
		}
		else
		{
			break;
		}
	}
	
	state = 0;
	offset = 0;
	counter = 0;
	direction = 0;
	hp = hp_state;
	
	attack = 0;
	attack_line = 0;
}




void Skeleton::setPosition( vector <float> x, vector <float> y )
{
	this->x = x;
	this->y = y;
}

void Skeleton::setLine( vector <int> line, vector <int> width )
{
	this->line = line;
	this->width = width;
}

void Skeleton::setDamage( int damage )
{
	this->damage = damage;
}

void Skeleton::setHP( int hp )
{
	this->hp = hp;
}

void Skeleton::setGlobalX( int startX, int endX )
{
	delay = 10;
	vel = 0.8;
	attack_line = 4;
	
	this->startX = startX;
	this->endX = endX;
}




void Skeleton::appear( int heroX )
{
	if( state == 0 )
	{
		if( heroX > startX -width[ 0 ] )
		{
			// printf( "appeared\n" );
			state = 1;
		}
	}
}

bool Skeleton::alive()
{
	if( state > 0 )
	{
		return true;
	}
	
	return false;
}

void Skeleton::walk( int heroX, int heroY, int w )
{
	sf::Uint8 gap = 10;
	
	if( direction == 2 || direction == 0 )
	{
		gap *= 2;
	}
	
	if( heroX +w >= startX &&
		heroX -w <= endX &&
		heroY >= y[ 0 ] && 
		heroY <= y[ 0 ] +w &&
		state < 4 )
	{
		if( heroX < x[ 0 ] -gap && x[ 0 ] > startX )
		{
			direction = 1;
		}
		else if( heroX > x[ 0 ] +gap && x[ 0 ] +width[ 0 ] < endX )
		{
			direction = 2;
		}
		else
		{
			if( direction == 1 )
			{
				direction = 3;
			}
			else if( direction == 2 )
			{
				direction = 0;
			}
		}
	}
	else
	{
		if( direction == 1 )
		{
			direction = 3;
		}
		else if( direction == 2 )
		{
			direction = 0;
		}
	}
}

void Skeleton::mechanics( int w )
{
	if( state > 0 )
	{
		offset ++;
		if( offset == line[ state -1 ]*delay )
		{
			attack ++;
			state = 2;	// reset
			offset = 0;
		}
			
		if( state == 1 )
		{
			if( offset == 0 )
			{
				state = 2;
			}
		}
		else if( state == 2 || state == 3 )
		{
			if( direction == 0 || direction == 3 )
			{
				if( offset >= line[ state -1 ]*delay )
				{
					offset = 0;
				}
				
				state = 2;
			}
			else if( direction == 1 )
			{
				state = 3;
				
				for( auto &it :x )
				{
					it -= vel;
				}
			}
			else if( direction == 2 )
			{
				state = 3;
				
				for( auto &it :x )
				{
					it += vel;
				}
			}
		}
		
		// printf( "%d %d\n", startX, endX );
	}
}

void Skeleton::ableAttack()
{
	if( state < 4 && attack > attack_line )
	{
		attack = 0;
		offset = 0;
		state = 4;
	}
}




float Skeleton::getX()
{
	if( direction == 2 || direction == 0 )
	{
		return x[ state -1 ] +width[ 0 ]/2;
	}
	
	if( state == 4 )
	{
		return x[ state -1 ] -30;
	}
	
	return x[ state -1 ];
}

float Skeleton::getY()
{
	return y[ state -1 ];
}

sf::Uint8 Skeleton::getDamage()
{
	return damage;
}

int Skeleton::getOffset()
{
	if( offset >= line[ state -1 ]*delay )
	{
		offset = 0;
	}
	
	return offset /delay;
}

int Skeleton::getNr()
{
	return state -1;
}

int Skeleton::get_x_scale()
{
	if( direction == 2 || direction == 0 )
	{
		return -1;
	}

	return 1;
}

bool Skeleton::harmAvailable()
{
	return false;
}



void Skeleton::moveX( int vel )
{
	for( auto &it :x )
	{
		it += vel;
	}
	
	startX += vel;
	endX += vel;
}
