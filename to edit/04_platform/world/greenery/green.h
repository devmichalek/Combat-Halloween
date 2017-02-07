#pragma once

#include "04_platform/world/brick/block.h"

class Green :public Block
{
	
public:

	bool bg;
	
	Green();
	~Green();
	void free();
};