#pragma once
#include "foeanimation.h"
#include "foefeatures.h"

class Skeleton: public FoeAnimation, public FoeFeaturesCommon
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

	Rect* realBox;
	Rect* attackBox;
	Rect* borderBox;
protected:
	virtual void setFPS();
public:
	Skeleton();
	virtual ~Skeleton();
	void free();
	
	virtual void marshial();
	void setInactionFrequency(float seconds = 4);
	void setAttackFrequency(float seconds = 1);
	float getHPScale();
	void setFeatures(std::vector<std::string> features);

	void moveX(const double &elapsedTime);
	void turnLeft();
	void turnRight();
	bool isLeftAlign() const;
	bool isRightAlign() const;

	// Sprite x, y
	virtual float getSpriteX();
	virtual float getSpriteY();

	// Real box and attack box
	virtual float getRealX();
	virtual float getRealY();
	virtual float getAttackX();
	virtual float getAttackY();

	// Text x, y
	float getMouthX();
	virtual float getMouthY();

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

	void mechanics( double &elapsedTime,
					Rect* &,
					Rect* &,
					bool &,
					float &,
					float &,
					float &
				  );
};