#pragma once

#include "platform/enemy/foes/skeleton/skeleton.h"

class Zombie :public Skeleton
{
	
public:
	
	// Getters.
	float getRealX();
	float getRealY();
	float getRealWidth();
	bool harmSomebody();
};