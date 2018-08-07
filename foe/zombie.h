#pragma once
#include "skeleton.h"

class Zombie: public Skeleton
{

public:
	float getX();
	float getY();
	float getRealX();
	float getRealWidth();
	float getRealHeight();
	float getAttackX();
	float getAttackWidth();
	float getMouthY();
	
	bool isAttacking(bool hide = false);
	void mechanics(double elapsedTime);
};