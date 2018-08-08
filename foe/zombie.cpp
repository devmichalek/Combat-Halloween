/*
#include "zombie.h"

float Zombie::getX()
{
	float xOffset = 0;
	
	if(scale < 0)
	{
		if(state == APPEAR)			xOffset = width *1.2121;
		else if(state == IDLE)		xOffset = width *1.12;
		else if(state == WALK)		xOffset = width *1.12;
		else if(state == ATTACK)	xOffset = width *1.58;
		else if(state == DIE)		xOffset = width *1.21;
	}
	else
	{
		if(state == ATTACK)			xOffset = -width *0.47;
		else if(state == DIE)		xOffset = -width *0.21;
	}
	
	return x + xOffset;
}

float Zombie::getY()
{
	float yOffset = width * 0.01;
	if(state == ATTACK)
	{
		yOffset += width * 0.032;
	}
		
	
	return y + yOffset;
}

float Zombie::getRealX()
{
	return x + (width * 0.22);
}

float Zombie::getRealWidth()
{
	return width / 1.5;
}

float Zombie::getRealHeight()
{
	return width * 1.26;
}

float Zombie::getAttackX()
{
	float myx = getRealX() - getAttackWidth();
	
	if(scale < 0)
	{
		myx += getRealX() + getRealWidth();
	}
	
	return myx;
}

float Zombie::getAttackWidth()
{
	return width * 0.5;
}

float Zombie::getMouthY()
{
	return getRealY() + width * 0.37;
}



bool Zombie::isAttacking(bool hide)
{
	if(state == ATTACK)
	{
		if(static_cast <int> (offset) == 3)
		{
			if(hide)
				return true;
			else if(attackNum == 0)
			{
				attackNum ++;
				return true;
			}
		}
		else if(static_cast <int> (offset) == 4)
		{
			if(hide)
				return true;
			else if(attackNum == 1)
			{
				attackNum ++;
				return true;
			}
		}
	}
	
	return false;
}

void Zombie::mechanics(double elapsedTime)
{
	if(state > -1)
	{
		offset += elapsedTime * 18;	// 18 offsets per second.
		
		if(state == APPEAR)
		{
			if(offset >= lines[APPEAR])
			{
				offset = 0;
				state = IDLE;
				appeared = true;
			}
		}
		
		if(inactionX != -1)
		{
			if(getRealX() + getRealWidth() < inactionX)
			{
				state = WALK;

				turnRight();

				moveX(elapsedTime);

				if(getRealX() + getRealWidth() > inactionX)
				{
					offset = 0;
					state = IDLE;
					inactionX = -1;
					inactionCounter = 0;
				}
			}
			else if(getRealX() > inactionX)
			{
				state = WALK;

				turnLeft();

				moveX(-elapsedTime);

				if(getRealX() < inactionX)
				{
					offset = 0;
					state = IDLE;
					inactionX = -1;
					inactionCounter = 0;
				}
			}
		}
		
		if(state == IDLE)
		{
			if(offset >= lines[IDLE])
			{
				offset = 0;
			}
			
			inactionCounter += elapsedTime;
			if(inactionCounter > inactionLine)
			{
				inactionLine = rand() % 5 + 3;
				inactionX = rand() % static_cast <int> (right - left) + left;
				offset = 0;
			}
		}
		
		
		if(state == WALK)
		{
			if(offset >= lines[WALK])
			{
				offset = 0;
			}
		}
		
		if(state == ATTACK)
		{
			if(offset >= lines[ATTACK])
			{
				attackNum = 0;
				offset = 0;
				state = IDLE;
			}
		}
		else
		{
			attackCounter += elapsedTime;
		}
		
		if(state == DIE)
		{
			if(offset >= lines[DIE])
			{
				offset = 0;
				state = -2;
			}
		}
	}
}
*/