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

	if (keys.empty()) // happens while testing
	{
		cmm::Keys k;
		k.loadKeys();
	}
}

bool KCoxing::isMovingLeft()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keys[KEY_ACTION::MOVE_LEFT]));
}

bool KCoxing::isMovingRight()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keys[KEY_ACTION::MOVE_RIGHT]));
}

bool KCoxing::isJumping()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keys[KEY_ACTION::JUMP]));
}

bool KCoxing::isAttacking()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keys[KEY_ACTION::ATTACK]));
}

bool KCoxing::isDefensing()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keys[KEY_ACTION::SHIELD]));
}
