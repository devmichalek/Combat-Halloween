#pragma once
#include "foenode.h"
#include "foeanimation.h"
#include "foefeatures.h"

class Skeleton: public FoeAnimation, public FoeFeatures
{
protected:
	enum ACTIONS
	{
		APPEAR = 0,
		IDLE,
		WALK,
		ATTACK,
		DIE
	};
	
	bool appeared;
	int attackNum;
	float attackLine;
	float attackCounter;
	float inactionX;
	float inactionLine;
	float inactionCounter;
	float inactionFrequency;

public:
	Skeleton();
	virtual ~Skeleton();
	void free();
	
	void setBoxes();
	void setInactionFrequency(float seconds = 4);
	void setAttackFrequency(float seconds = 1);
	float getHPScale();

	void moveX(double elapsedTime);
	void turnLeft();
	void turnRight();
	bool isLeftAlign() const;
	bool isRightAlign() const;

	// Sprite x, y
	float getSpriteX();
	float getSpriteY();

	// Real box and attack box
	float getRealX();
	float getRealY();
	float getAttackX();
	float getAttackY();

	// Text x, y
	float getMouthX();
	float getMouthY();

	// Actions
	void setAppear();
	void setIdle();
	void setWalk();
	void setAttack();
	void setDie();

	bool isAlive();
	bool isAbleToAppear();
	bool isAbleToWalk();
	bool isAbleToAttack();
	bool isAttackDone();
	bool isAttacking();

	void mechanics(	double &elapsedTime,
					Rect* &,
					Rect* &,
					bool &,
					float &,
					float &,
					float &
				  );
};