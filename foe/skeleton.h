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
protected:
	void setFPS();
	virtual void setBoxes();
public:
	void setInactionFrequency(float seconds = 4);
	void setAttackFrequency(float seconds = 1);
	float getHPScale();
protected:
	void moveX(const double &elapsedTime);
	void turnLeft();
	void turnRight();
	bool isLeftAlign() const;
	bool isRightAlign() const;
public:
	// Sprite x, y
	virtual float getSpriteX();
	virtual float getSpriteY();
protected:
	// Real box and attack box
	virtual float getRealX();
	virtual float getRealY();
	virtual float getAttackX();
	virtual float getAttackY();
public:
	// Text x, y
	float getMouthX();
	virtual float getMouthY();
protected:
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
	virtual bool isAttacking();
public:
	void mechanics( double &elapsedTime,
					Rect* &,
					Rect* &,
					bool &,
					float &,
					float &,
					float &
				  );
};