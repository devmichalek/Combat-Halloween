#pragma once
#include "skeleton.h"

class Zombie final : public Skeleton
{
	void setFPS();
	void marshial();
public:
	// Sprite x, y
	float getSpriteX();
	float getSpriteY();
private:
	// Real box and attack box
	float getRealX();
	float getAttackX();
public:
	// Text x, y
	float getMouthY();
private:
	bool isAttacking();
};