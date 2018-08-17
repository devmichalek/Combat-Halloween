pragma once
#include "skeleton.h"

class Zombie: public Skeleton
{
	void setFPS();
	void setBoxes();
public:
	// Sprite x, y
	float getSpriteX();
	float getSpriteY();
private:
	// Real box and attack box
	float getRealX();
	float getRealY();
	float getAttackX();
	float getAttackY();
public:
	// Text x, y
	float getMouthY();
private:
	bool isAttacking();
};