#include "kcoxing.h"
#include <SFML/Window/Keyboard.hpp>

pla::KCoxing::KCoxing()
{
	reset();
}

pla::KCoxing::~KCoxing()
{
	reset();
}

void pla::KCoxing::reset()
{
	walkTimer = 0;
	walkLine = 1.0f;

	jumpCounter = 0;
	jumpLine = 2;	 // max 2 jumps in a row
	jumpReleased = true;
	falling = false;

	attack = false;
	jump = false;
	die = false;

	if (keys.empty()) // happens while testing
	{
		cmm::Keys k;
		k.loadKeys();
	}
}

bool pla::KCoxing::isMovingLeft()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keys[KEY_ACTION::MOVE_LEFT]));
}

bool pla::KCoxing::isMovingRight()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keys[KEY_ACTION::MOVE_RIGHT]));
}

bool pla::KCoxing::isJumping()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keys[KEY_ACTION::JUMP])) && (jumpCounter < jumpLine) && jumpReleased;
}

void pla::KCoxing::releaseJumping(const sf::Event &event)
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

bool pla::KCoxing::isAttacking()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keys[KEY_ACTION::ATTACK]));
}

bool pla::KCoxing::isDefensing()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keys[KEY_ACTION::SHIELD]));
}
