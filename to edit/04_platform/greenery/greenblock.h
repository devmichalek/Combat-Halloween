#pragma once

#include "04_platform/world/block.h"

class GreenBlock :public Block
{
	
public:

	bool bg;
	
	GreenBlock();
	~GreenBlock();
	void free();
};