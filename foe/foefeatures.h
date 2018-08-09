#pragma once
#include "foenode.h"

class FoeFeatures : virtual public FoeNode
{
protected:
	float armour;
	float damage;
	float velocity;
	float heartPoints, hp;

public:
	FoeFeatures();
	virtual ~FoeFeatures();

	void setArmour(float newArmour);
	void setDamage(float newDamage);
	void setVelocity(float newVelocity);
	void setHeartPoints(float newHeartPoints);
	virtual float getHPScale() = 0;

protected:
	// const float getArmour() const;
	// const float getDamage() const;
	// const float getVelocity() const;
	// const float getHeartPoints() const;
	void harm(float value);
	virtual void setDie() = 0;
};