#pragma once

#include "04_platform/world/spikes/spike.h"

class Saw :public Spike
{
	double angle;
	
public:

	using Spike::Spike;
	void free();
	void mechanics();
	double getAngle();
};