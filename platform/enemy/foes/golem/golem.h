#pragma once

#include "platform/enemy/foes/skeleton/skeleton.h"

class Golem :public Skeleton
{
	enum
	{
		APPEAR = 0,
		WALK,
		ATTACK,
		DEAD
	};
	
public:
	
	using Skeleton::Skeleton;
	
	// Setters.
	void setDead();
	
	// Getters.
	float getRealX();
	float getRealY();
	float getRealWidth();
	
	float getAttackX();
	float getAttackY();
	int getAttackHeight();
	int getAttackWidth();
	
	bool isAlive();
	bool harmSomebody();
	
	// Activity.
	void appear( Rect* rect );
	void walk( Rect* rect );
	void mechanics();
	void ableAttack();
};