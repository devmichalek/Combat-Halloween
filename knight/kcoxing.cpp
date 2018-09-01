#include "kcoxing.h"
#include <SFML/Window/Keyboard.hpp>

KCoxing::KCoxing()
{
	reset();
}

KCoxing::~KCoxing()
{
	reset();
}

void KCoxing::reset()
{
	walkTimer = 0;
	walkLine = 1.5;

	jumpCounter = 0;
	jumpLine = 2;	 // max 2 jumps in a row
}

bool KCoxing::isMovingLeft()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keys[0]));
}

bool KCoxing::isMovingRight()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keys[1]));
}

bool KCoxing::isJumping()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keys[2]));
}

bool KCoxing::isAttacking()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keys[3]));
}

bool KCoxing::isDefensing()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keys[4]));
}
