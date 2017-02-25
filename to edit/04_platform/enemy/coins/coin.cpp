#include "04_platform/enemy/coins/coin.h"
#include <stdio.h>

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
	corner = false;
	x = y = yLine = 0;
	left = right = 0;
	
	jumpState = 0;
	
	direction = 0;
	offset = 0;
}



void Coin::setPosition( int x, int y )
{
	this->x = x;
	this->y = yLine = y;
}

void Coin::setBorders( int left, int right )
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

void Coin::setCorner()
{
	corner = true;
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

void Coin::mechanics()
{
	if( active )
	{
		offset ++;
		if( offset == line *delay )
		{
			offset = 0;
		}
		
		if( !corner )
		{
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
					}
				}
			}
			else if( y < yLine )
			{
				y += vel;
			}
		}
	}
}

bool Coin::moveToCorner( int x, int y )
{
	if( corner )
	{
		// printf( "sth\n" );
		bool added = true;
		if( this->x < x )
		{
			this->x += 8;
			// printf( "sth\n" );
			added = false;
		}
		
		if( this->y > y )
		{
			this->y -= 7;
			// printf( "st2h\n" );
			added = false;
		}
		
		// printf( "%d\n", added );
		return added;
	}
	
	return false;
}

void Coin::moveX( int vel )
{
	if( !corner )
	{
		x += vel;
		left += vel;
		right += vel;
	}
}