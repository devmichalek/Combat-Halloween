#pragma once
#include "foeanimation.h"

struct XYNode: public FoeAnimation
{
	int ID;
	float cX, cY;	// center x, center y

	XYNode(float cX = -1, float cY = -1, int ID = -1);
	virtual ~XYNode();
	void set(float cX = -1, float cY = -1, int ID = -1);

	virtual const float& getArmour() const = 0;
	virtual const float& getDamage() const = 0;
	virtual const float& getVelocity() const = 0;
	virtual const float& getHeartPoints() const = 0;
	virtual void harm(float value) = 0;
	virtual float getHPScale() = 0;

	virtual float getX() = 0;
	virtual float getY() = 0;

	virtual float getRealX() = 0;
	virtual float getRealY() = 0;
	virtual float getRealWidth() = 0;
	virtual float getRealHeight() = 0;

	virtual float getAttackX() = 0;
	virtual float getAttackY() = 0;
	virtual float getAttackWidth() = 0;
	virtual float getAttackHeight() = 0;

	virtual float getMouthX() = 0;
	virtual float getMouthY() = 0;

	// virtual const float& getLeft() const = 0;
	// virtual const float& getRight() const = 0;
	virtual bool isAlive() const = 0;
	virtual bool isAttacking() = 0;
	virtual void mechanics(double elapsedTime) = 0;
};