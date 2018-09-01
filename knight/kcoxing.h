#pragma once
#include "coxing.h"

class KCoxing : public Coxing
{
public:
	float walkTimer;
	float walkLine;

	sf::Int8 jumpCounter;
	sf::Int8 jumpLine;

	KCoxing();
	~KCoxing();
	void reset();

	bool isMovingLeft();
	bool isMovingRight();
	bool isJumping();
	bool isAttacking();
	bool isDefensing();	// using shield
};

/*
MOVE_LEFT = 0,
MOVE_RIGHT,
JUMP,
ATTACK,
SHIELD,
*/