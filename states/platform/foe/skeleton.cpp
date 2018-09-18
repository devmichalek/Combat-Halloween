#include "skeleton.h"
#include <boost/lexical_cast.hpp>

Skeleton::Skeleton()
{
	realBox = nullptr;
	attackBox = nullptr;
	borderBox = nullptr;
	free();
}

Skeleton::~Skeleton()
{
	free();
}

void Skeleton::free()
{
	appeared = false;
	attackNum = 0;
	attackLine = 1;
	attackCounter = attackLine;
	inactionFrequency = 4;
	inactionX = -1;
	inactionLine = rand() % static_cast <int>(inactionFrequency) + inactionFrequency;
	inactionCounter = -1;

	if (realBox)
	{
		delete realBox;
		realBox = nullptr;
	}
	
	if (attackBox)
	{
		delete attackBox;
		attackBox = nullptr;
	}

	if (borderBox)
	{
		delete borderBox;
		borderBox = nullptr;
	}
}

void Skeleton::setFPS()
{
	FPS = 20.0f;
}



void Skeleton::marshial()
{
	realBox = new Rect;
	realBox->width = width / 2.0f;
	realBox->height = width * 1.26f;

	attackBox = new Rect;
	attackBox->width = width * 0.43f;
	attackBox->height = width * 0.6f;

	borderBox = new Rect;
	borderBox->width = right - left;
	borderBox->height = realBox->height;
	borderBox->left = left;
	borderBox->top = y;	// was: y + realBox->height
}

void Skeleton::setInactionFrequency(float seconds)
{
	inactionFrequency = seconds;
}

void Skeleton::setAttackFrequency(float seconds)
{
	attackLine = seconds;
}

float Skeleton::getHPScale()
{
	return heartPoints / hp < 0 ? 0 : heartPoints / hp;
}

void Skeleton::setFeatures(std::vector<std::string> features)
{
	setArmour(boost::lexical_cast<float>(features[0]));
	setDamage(boost::lexical_cast<float>(features[1]));
	setVelocity(boost::lexical_cast<float>(features[2]));
	setHeartPoints(boost::lexical_cast<float>(features[3]));
	setInactionFrequency(boost::lexical_cast<float>(features[4]));
	setAttackFrequency(boost::lexical_cast<float>(features[5]));
}



void Skeleton::moveX(const double &elapsedTime)
{
	if (isAttackDone())
	{
		x += ((float)elapsedTime * velocity);
	}
}

void Skeleton::turnLeft()
{
	if (isRightAlign() && isAttackDone())
	{
		scale = -scale;
	}
}

void Skeleton::turnRight()
{
	if (isLeftAlign() && isAttackDone())
	{
		scale = -scale;
	}
}

bool Skeleton::isLeftAlign() const
{
	return scale > 0;
}

bool Skeleton::isRightAlign() const
{
	return scale < 0;
}



float Skeleton::getSpriteX()
{
	float xOffset = 0;

	if (scale < 0)
	{
		if (state == APPEAR)		xOffset = width * 0.70f;
		else if (state == IDLE)		xOffset = width * 0.59f;
		else if (state == WALK)		xOffset = width * 0.59f;
		else if (state == ATTACK)	xOffset = width * 1.01f;
		else if (state == DIE)		xOffset = width * 1.01f;
	}
	else
	{
		if (state == ATTACK)		xOffset = -width * 0.42f;
		else if (state == DIE)		xOffset = -width * 0.42f;
	}

	return x + xOffset;
}

float Skeleton::getSpriteY()
{
	return y;
}



float Skeleton::getRealX()
{
	return x + (width * 0.05f);
}

float Skeleton::getRealY()
{
	return y - realBox->height;
}

float Skeleton::getAttackX()
{
	float myx = getRealX() - realBox->width;

	if (scale < 0)
	{
		myx += realBox->width * 2;
	}

	return myx;
}

float Skeleton::getAttackY()
{
	return getRealY() + width * 0.5f;
}



float Skeleton::getMouthX()
{
	return getRealX() + realBox->width / 1.5f;
}

float Skeleton::getMouthY()
{
	return getRealY() + width * 0.45f;
}



void Skeleton::setAppear()
{
	state = APPEAR;
	offset = 0;
	inactionX = -1;
	inactionCounter = 0;
}

void Skeleton::setIdle()
{
	if (appeared && state != ATTACK)
	{
		state = IDLE;
	}
}

void Skeleton::setWalk()
{
	if (isAttackDone())
	{
		state = WALK;
		inactionX = -1;
		inactionCounter = 0;
	}
}

void Skeleton::setAttack()
{
	state = ATTACK;
	offset = 0;
	attackCounter = 0;
	inactionX = -1;
	inactionCounter = 0;
}

void Skeleton::setDie()
{
	state = DIE;
	offset = 0;
	inactionX = -1;
	inactionCounter = 0;
}



bool Skeleton::isAlive()
{
	return state > -2 && state != DIE;
}

bool Skeleton::isAbleToAppear()
{
	return state == -1;
}

bool Skeleton::isAbleToWalk()
{
	return state == IDLE || state == WALK;
}

bool Skeleton::isAbleToAttack()
{
	return isAbleToWalk() && attackCounter > attackLine;
}

bool Skeleton::isAttackDone()
{
	return attackCounter > attackLine / 3;
}

bool Skeleton::isAttacking()
{
	if (state == ATTACK)
	{
		if (static_cast <int> (offset) == 3 && attackNum == 0)
		{
			++attackNum;
			return true;
		}
		else if (static_cast <int> (offset) == 6 && attackNum == 1)
		{
			++attackNum;
			return true;
		}
	}

	return false;
}



void Skeleton::mechanics(	double &elapsedTime,
							Rect* &character,
							Rect* &characterAttack,
							bool &characterHasAttacked,
							float &characterDamage,
							float &characterHP,
							float &characterArmour
						)
{
	if (isAlive())
	{
		if (characterHasAttacked)
		{
			realBox->left = getRealX();
			realBox->top = getRealY();

			if (realBox->intersects(*characterAttack))
			{
				harm(characterDamage);
			}
		}

		if (isAttacking())
		{
			attackBox->left = getRealX();
			attackBox->top = getRealY();

			if (attackBox->intersects(*character))
			{
				characterHP -= (damage - (damage * characterArmour / 1000));
			}
		}
		else
		{
			setIdle();
		}

	
		if (borderBox->intersects(*character))
		{
			if (isAbleToWalk())
			{
				realBox->left = getRealX();

				if (realBox->left + realBox->width / 2 < character->left + character->width / 2)
					turnRight();
				else
					turnLeft();
				setWalk();

				if (realBox->left + realBox->width < right && realBox->left + realBox->width < character->left)
				{
					moveX(elapsedTime);
				}
				else if (realBox->left > left && realBox->left > character->left + character->width)
				{
					moveX(-elapsedTime);
				}
				else if (isAbleToAttack())
				{
					setAttack();
				}
				else
				{
					state = IDLE;
				}
			}
			else if (isAbleToAppear())
			{
				if (getRealX() + realBox->width / 2 < character->left + character->width / 2)
					turnRight();
				else
					turnLeft();
				setAppear();
			}
		}
	}

	offset += elapsedTime * FPS;

	if (state == APPEAR)
	{
		if (offset >= lines[APPEAR])
		{
			offset = 0;
			state = IDLE;
			appeared = true;
		}
	}

	if (!appeared)
		return;

	if (inactionX != -1)
	{
		realBox->left = getRealX();

		if (realBox->left + realBox->width < inactionX)
		{
			state = WALK;
			turnRight();
			moveX(elapsedTime);
			realBox->left = getRealX();
			if (realBox->left + realBox->width > inactionX)
			{
				offset = 0;
				state = IDLE;
				inactionX = -1;
				inactionCounter = 0;
			}
		}
		else if (realBox->left > inactionX)
		{
			state = WALK;
			turnLeft();
			moveX(-elapsedTime);
			realBox->left = getRealX();
			if (realBox->left < inactionX)
			{
				offset = 0;
				state = IDLE;
				inactionX = -1;
				inactionCounter = 0;
			}
		}
	}

	if (state == IDLE)
	{
		if (offset >= lines[IDLE])
		{
			offset = 0;
		}

		inactionCounter += (float)elapsedTime;
		if (inactionCounter > inactionLine)
		{
			offset = 0;
			inactionX = rand() % static_cast <int> (right - left) + left;
			inactionLine = rand() % static_cast <int> (inactionFrequency) + inactionFrequency;
		}
	}


	if (state == WALK)
	{
		if (offset >= lines[WALK])
		{
			offset = 0;
		}
	}

	if (state == ATTACK)
	{
		if (offset >= lines[ATTACK])
		{
			attackNum = 0;
			offset = 0;
			state = IDLE;
		}
	}
	else
	{
		attackCounter += (float)elapsedTime;
	}

	if (state == DIE)
	{
		if (offset >= lines[DIE])
		{
			offset = 0;
			state = -2;
		}
	}
}