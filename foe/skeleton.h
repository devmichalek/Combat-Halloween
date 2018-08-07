#pragma once
#include "xynode.h"
#include "foeanimation.h"

class Skeleton: public XYNode, public FoeAnimation
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

	// Features
	float armour;
	float damage;
	float velocity;
	float heartPoints, hp;

	// Positioning
	float x, y;
	float scale;
	float width;
	float left, right; // x borders

	// Support
	bool appeared;
	int attackNum;
	float attackLine;
	float attackCounter;
	float inactionX;
	float inactionLine;
	float inactionCounter;
	float walkFrequency;

public:
	Skeleton();
	virtual ~Skeleton();
	void free();

	// Features
	void setArmour(float value);
	void setDamage(float value);
	void setVelocity(float value);
	void setHeartPoints(float value);
	void setWalkFrequency(float seconds = 4);
	void setAttackFrequency(float seconds = 1);
	const float& getArmour() const;
	const float& getDamage() const;
	const float& getVelocity() const;
	const float& getHeartPoints() const;
	void harm(float value);
	float getHPScale();


	// Positioning.
	void setScale(float newScale);
	void setWidth(float newWidth);
	void setPosition(float newX, float newY);
	void setBorders(float newLeft, float newRight);

	void moveX(double elapsedTime);
	void turnLeft();
	void turnRight();

	float getX();
	float getY();

	float getRealX();
	float getRealY();
	float getRealWidth();
	float getRealHeight();

	float getAttackX();
	float getAttackY();
	float getAttackWidth();
	float getAttackHeight();

	float getMouthX();
	float getMouthY();

	bool isLeftAlign();
	bool isRightAlign();

	const float& getScaleX() const;
	float getScaleY();
	const float& getWidth() const;
	const float& getLeft() const;
	const float& getRight() const;


	// Set Action
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
	bool isAttacking(bool hide = false);
	void mechanics(double elapsedTime);
};