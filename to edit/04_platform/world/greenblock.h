#pragma once

#include "block.h"

class GreenBlock :public Block
{
	
public:

	bool bg;
	
	GreenBlock();
	~GreenBlock();
	void free();
};