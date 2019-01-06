#include "kspecs.h"
#include "colors.h"

pla::KSpecs::KSpecs()
{
	free();
}

pla::KSpecs::~KSpecs()
{
	free();
}

void pla::KSpecs::free()
{
	hp = mp = 0;
	armour = mresistant = 0;
	velocity = hvelocity = 0;
	gravity = 0;
	damage = mdamage = 0;
	luck = 0;
	experience = 0;
	level = 0;
	scale = 0.45f;
}

void pla::KSpecs::prepare()
{
	if (features.empty())
		features.resize(Specs::SIZE);

	hp = static_cast<float>(features[HEART_POINTS]);
	mp = static_cast<float>(features[MAGIC_POINTS]);

	armour =		static_cast<float>(features[ARMOUR]);
	mresistant =	static_cast<float>(features[MAGIC_RESISTANT]);

	velocity =	MAX_ALPHA + MAX_ALPHA * static_cast<float>(features[MOVEMENT_SPEED]) / 100;
	hvelocity =	velocity / 2;
	gravity =	MAX_ALPHA;

	damage =	static_cast<float>(features[DAMAGE]);
	mdamage =	static_cast<float>(features[MAGIC_DAMAGE]);

	luck =			static_cast<float>(features[LUCK]);
	experience =	static_cast<float>(features[EXPERIENCE]);
	level =			features[LEVEL];
}

void pla::KSpecs::set(int i, int value)
{
	if (features.empty())
		features.resize(Specs::SIZE);
	features[i] = value;
}