#pragma once
#include "foe.h"

class FoeFeaturesCommon : virtual public Foe
{
protected:
	float armour;
	float damage;
	float velocity;
	float heartPoints, hp;

public:
	FoeFeaturesCommon();
	virtual ~FoeFeaturesCommon();

	void setArmour(float newArmour);
	void setDamage(float newDamage);
	void setVelocity(float newVelocity);
	void setHeartPoints(float newHeartPoints);
	virtual float getHPScale() = 0;
	virtual void setFeatures(std::vector<std::string> features);

protected:
	// const float getArmour() const;
	// const float getDamage() const;
	// const float getVelocity() const;
	// const float getHeartPoints() const;
	void harm(const float &value);
	virtual void setDie() = 0;
};