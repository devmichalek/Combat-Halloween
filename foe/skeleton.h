#pragma once
#include "xynode.h"
#include <vector>
#include <string>

class Skeleton :public XYNode
{
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
	float left, right; // x borders

	// Animation
	int state;
	float offset;
	std::vector<int> lines;

	// Text
	int chosenText;
	float textLine;
	float textCounter;
	float textFrequency;
	std::vector<std::string> texts;

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
	~Skeleton();
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
	void moveX(double elapsedTime);
	void setPosition(float x, float y);
	void setWidth(float width);
	void setCenterX(float centerX);
	void setBorders(float left, float right);
	void setScale(float scale);
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
	float getCenterX();
	const float& getLeft() const;
	const float& getRight() const;
	const float& getScaleX() const;
	float getScaleY();

	// Animation
	void setState(int value);
	void setOffset(float value);
	void setLines(std::vector<int> lines);
	const int& getState() const;
	const float& getOffset() const;
	const std::vector<int>& getLines() const;


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


	// Text.
	void setTextFrequency(float seconds = 8);
	void setText();
	void addText(std::string line);
	bool showText();
	const std::string& getText() const;
	bool isLeftText();
};