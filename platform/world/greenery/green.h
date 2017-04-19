#pragma once

#include "platform/world/brick/block.h"

class Green :public Block
{
	
public:

	bool bg;
	
	Green();
	~Green();
	void free();
};