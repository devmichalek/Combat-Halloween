#pragma once
#include "coxing.h"
#include <SFML/Network/Packet.hpp>

class KCoxing : public cmm::Coxing
{
public:
	float walkTimer;
	float walkLine;

	sf::Int8 jumpCounter;
	sf::Int8 jumpLine;

	bool attack;
	bool jump;
	bool die;

	KCoxing();
	~KCoxing();
	void reset();

	bool isMovingLeft();
	bool isMovingRight();
	bool isJumping();
	bool isAttacking();
	bool isDefensing();	// using shield
};