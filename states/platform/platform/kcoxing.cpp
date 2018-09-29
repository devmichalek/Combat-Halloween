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
	walkLine = 1.0f;

	jumpCounter = 0;
	jumpLine = 2;	 // max 2 jumps in a row
	jumpReleased = true;

	attack = false;
	jump = false;
	die = false;

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
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keys[KEY_ACTION::JUMP])) && (jumpCounter < jumpLine) && jumpReleased;
}

void KCoxing::releaseJumping(const sf::Event &event)
{
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::Key(keys[KEY_ACTION::JUMP]))
		{
			if (jumpCounter > 0)
			{
				jumpReleased = true;
			}
		}
	}
}

bool KCoxing::isAttacking()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keys[KEY_ACTION::ATTACK]));
}

bool KCoxing::isDefensing()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keys[KEY_ACTION::SHIELD]));
}
