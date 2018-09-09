#pragma once
#include "specs.h"

class KSpecs : public Specs// Knight Specs
{
public:
	float hp;
	float mp;
	float armour;
	float mresistant;
	float velocity;
	float hvelocity;	// half velocity
	float damage;
	float mdamage;
	float luck;
	float experience;
	int level;

	// other
	float scale;

	KSpecs();
	~KSpecs();
private:
	void freeSpecs();
public:
	void setSpecs();	// also reset
};