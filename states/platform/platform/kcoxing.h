#pragma once
#include "coxing.h"
#include <SFML/Window/Event.hpp>

class KCoxing : public cmm::Coxing
{
public:
	float walkTimer;
	float walkLine;

	char jumpCounter;
	char jumpLine;
	bool jumpReleased;
	bool falling;

	bool attack;
	bool jump;
	bool die;

	KCoxing();
	~KCoxing();
	void reset();

	bool isMovingLeft();
	bool isMovingRight();
	bool isJumping();
	void releaseJumping(const sf::Event &event);
	bool isAttacking();
	bool isDefensing();	// using shield
};