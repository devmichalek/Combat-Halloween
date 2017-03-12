#pragma once

#include "04_platform/enemy/skeleton/skeleton.h"

class Zombie :public Skeleton
{
	
public:
	
	// Getters.
	float getRealX();
	float getRealY();
	float getRealWidth();
	bool harmSomebody();
};