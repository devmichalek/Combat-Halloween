#include "kspecs.h"

KSpecs::KSpecs()
{
	freeSpecs();
}

KSpecs::~KSpecs()
{
	freeSpecs();
}

void KSpecs::freeSpecs()
{
	hp = 0;
	mp = 0;
	armour = 0;
	mresistant = 0;
	velocity = 0;
	hvelocity = 0;
	gravity = 0;
	damage = 0;
	mdamage = 0;
	luck = 0;
	experience = 0;
	level = 0;
	scale = 0.45f;
}

void KSpecs::setSpecs()
{
	if (features.empty())	// happens while testing
	{
		features.push_back(20);
		features.push_back(10);
		features.push_back(50);
		features.push_back(30);
		features.push_back(25);
		features.push_back(4);
		features.push_back(2);
		features.push_back(10);
		features.push_back(0);
		features.push_back(1);
	}

	hp = static_cast<float>(features[HEART_POINTS]);
	mp = static_cast<float>(features[MAGIC_POINTS]);
	armour = static_cast<float>(features[ARMOUR]);
	mresistant = static_cast<float>(features[MAGIC_RESISTANT]);
	velocity = 0xFF + 0xFF * static_cast<float>(features[MOVEMENT_SPEED]) / 100;
	hvelocity = velocity / 2;
	gravity = 0.5;	// change later
	damage = static_cast<float>(features[DAMAGE]);
	mdamage = static_cast<float>(features[MAGIC_DAMAGE]);
	luck = static_cast<float>(features[LUCK]);
	experience = static_cast<float>(features[EXPERIENCE]);
	level = features[LEVEL];
}