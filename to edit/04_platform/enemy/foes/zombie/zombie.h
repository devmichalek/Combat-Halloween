#pragma once

#include "04_platform/enemy/foes/skeleton/skeleton.h"

class Zombie :public Skeleton
{
	
public:
	
	// Getters.
	float getRealX();
	float getRealY();
	float getRealWidth();
	bool harmSomebody();
};