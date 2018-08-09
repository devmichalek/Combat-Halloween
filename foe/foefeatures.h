#pragma once

class FoeFeatures
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

	const float& getArmour() const;
	const float& getDamage() const;
	const float& getVelocity() const;
	const float& getHeartPoints() const;

	void harm(float value);
	virtual void setDie() = 0;
	virtual float getHPScale() = 0;
};