#pragma once

#include "04_platform/enemy/skeleton/skeleton.h"

class Vampire :public Skeleton
{
	enum
	{
		APPEAR = 0,
		WALK,
		ATTACK,
		DEAD
	};
	
public:

	// Setters.
	void setDead();
	
	// Getters.
	float getX();
	float getY();
	
	float getRealX();
	float getRealY();
	float getRealWidth();
	
	float getAttackX();
	float getAttackY();
	int getAttackWidth();
	int getAttackHeight();
	
	int8_t getState();
	sf::Uint8 getOffset();
	bool isAlive();
	bool harmSomebody();
	
	
	// Activity.
	void appear( Rect* rect );
	void walk( Rect* rect );
	void mechanics();
	void ableAttack();
};