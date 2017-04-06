#include "coin.h"
// #include <stdio.h>

Coin::Coin()
{
	free();
}

Coin::~Coin()
{
	free();
}

void Coin::free()
{
	reset();
	
	vel = 0;
	delay = 0;
	line = 0;
	jump = 0;
}

void Coin::reset()
{
	active = false;
	x = y = yLine = 0;
	left = right = 0;
	
	jumpState = 0;
	
	direction = 0;
	offset = 0;
}



void Coin::setPosition( float x, float y )
{
	this->x = x;
	this->y = yLine = y;
}

void Coin::setBorders( float left, float right )
{
	this->left = left;
	this->right = right;
}

void Coin::setJump( int jump )
{
	jumpState = 0;
	// printf( "%d\n", jump );
	this->jump = jump;
}


void Coin::setAsActive()
{
	jumpState = 1;
	y -= jump;
	active = true;
}

void Coin::setVelocity( float vel )
{
	// printf( "%f\n", vel );
	this->vel = vel;
}

void Coin::setDirection( sf::Uint8 direction )
{
	// printf( "%d\n", direction );
	this->direction = direction;
}

void Coin::setLine( int line )
{
	this->line = line;
}

void Coin::setDelay( int delay )
{
	this->delay = delay;
}



int Coin::getOffset()
{
	return offset /delay;
}

int Coin::getX()
{
	return x;
}

int Coin::getY()
{
	return y;
}

bool Coin::isActive()
{
	return active;
}

bool Coin::mechanics()
{
	if( active )
	{
		offset ++;
		if( offset == line *delay )
		{
			offset = 0;
		}
		
		if( jump > 0 )
		{
			if( x < right && x > left )
			{
				if( direction == 1 )
				{
					x += vel;
				}
				else if( direction == 2 )
				{
					x -= vel;
				}
			}
			
			if( jumpState == 0 )
			{
				if( y > yLine -jump )
				{
					y -= 2;
				}
				else
				{
					// printf( "happen1\n" );
					jump /= 3;
					jumpState = 1;
				}
			}
			else
			{
				if( y < yLine )
				{
					y += 2;
				}
				else
				{
					// printf( "happen2\n" );
					jumpState = 0;
					return true;
				}
			}
		}
		else if( y < yLine )
		{
			y += vel;
		}
	}
	
	return false;
}

void Coin::moveX( float vel )
{
	x += vel;
	left += vel;
	right += vel;
}