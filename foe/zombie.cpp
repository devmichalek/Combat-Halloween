#include "zombie.h"

void Zombie::setFPS()
{
	FPS = 18.0f;
}

void Zombie::setBoxes()
{
	realBox = new Rect;
	realBox->width = width / 1.5f;
	realBox->height = width * 1.26f;

	attackBox = new Rect;
	attackBox->width = width * 0.5;
	attackBox->height = width * 0.6f;

	borderBox = new Rect;
	borderBox->width = right - left;
	borderBox->height = realBox->height;
	borderBox->left = left;
	borderBox->top = y + realBox->height;
}

float Zombie::getSpriteX()
{
	float xOffset = 0;
	
	if(scale < 0)
	{
		if(state == APPEAR)			xOffset = width *1.2121f;
		else if(state == IDLE)		xOffset = width *1.12f;
		else if(state == WALK)		xOffset = width *1.12f;
		else if(state == ATTACK)	xOffset = width *1.58f;
		else if(state == DIE)		xOffset = width *1.21f;
	}
	else
	{
		if(state == ATTACK)			xOffset = -width *0.47f;
		else if(state == DIE)		xOffset = -width *0.21f;
	}
	
	return x + xOffset;
}

float Zombie::getSpriteY()
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

float Zombie::getAttackX()
{
	float myx = getRealX() - attackBox->width;
	
	if(scale < 0)
	{
		myx += realBox->width;
	}
	
	return myx;
}

float Zombie::getMouthY()
{
	return getRealY() + width * 0.37;
}

bool Zombie::isAttacking()
{
	if (state == ATTACK)
	{
		if (static_cast <int> (offset) == 3 && attackNum == 0)
		{
			attackNum++;
			return true;
		}
		else if (static_cast <int> (offset) == 4 && attackNum == 1)
		{
			attackNum++;
			return true;
		}
	}

	return false;
}