#include "foefeatures.h"
#include <boost/lexical_cast.hpp>

FoeFeaturesCommon::FoeFeaturesCommon()
{
	armour = 0;
	damage = 0;
	velocity = 0;
	heartPoints = hp = 0;
}

FoeFeaturesCommon::~FoeFeaturesCommon()
{
	armour = 0;
	damage = 0;
	velocity = 0;
	heartPoints = hp = 0;
}



void FoeFeaturesCommon::setArmour(float newArmour)
{
	armour = newArmour;
}

void FoeFeaturesCommon::setDamage(float newDamage)
{
	damage = newDamage;
}

void FoeFeaturesCommon::setVelocity(float newVelocity)
{
	velocity = newVelocity;
}

void FoeFeaturesCommon::setHeartPoints(float newHeartPoints)
{
	heartPoints = hp = newHeartPoints;
}

void FoeFeaturesCommon::setFeatures(std::vector<std::string> features)
{
	setArmour(boost::lexical_cast<float>(features[0]));
	setDamage(boost::lexical_cast<float>(features[1]));
	setVelocity(boost::lexical_cast<float>(features[2]));
	setHeartPoints(boost::lexical_cast<float>(features[3]));
}

/*
const float FoeFeaturesCommon::getArmour() const
{
	return armour;
}

const float FoeFeaturesCommon::getDamage() const
{
	return damage;
}

const float FoeFeaturesCommon::getVelocity() const
{
	return velocity;
}

const float FoeFeaturesCommon::getHeartPoints() const
{
	return heartPoints;
}
*/

void FoeFeaturesCommon::harm(const float &value)
{
	heartPoints -= (value - (value * armour / 1000));

	if (heartPoints <= 0)
	{
		setDie();
	}
}