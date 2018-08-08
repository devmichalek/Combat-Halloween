#include "foefeatures.h"

FoeFeatures::FoeFeatures()
{
	armour = 0;
	damage = 0;
	velocity = 0;
	heartPoints = hp = 0;
}

FoeFeatures::~FoeFeatures()
{
	armour = 0;
	damage = 0;
	velocity = 0;
	heartPoints = hp = 0;
}



void FoeFeatures::setArmour(float newArmour)
{
	armour = newArmour;
}

void FoeFeatures::setDamage(float newDamage)
{
	damage = newDamage;
}

void FoeFeatures::setVelocity(float newVelocity)
{
	velocity = newVelocity;
}

void FoeFeatures::setHeartPoints(float newHeartPoints)
{
	heartPoints = hp = newHeartPoints;
}

const float& FoeFeatures::getArmour() const
{
	return armour;
}

const float& FoeFeatures::getDamage() const
{
	return damage;
}

const float& FoeFeatures::getVelocity() const
{
	return velocity;
}

const float& FoeFeatures::getHeartPoints() const
{
	return heartPoints;
}


void FoeFeatures::harm(float value)
{
	heartPoints -= (value - (value * armour / 1000));

	if (heartPoints <= 0)
	{
		setDie();
	}
}