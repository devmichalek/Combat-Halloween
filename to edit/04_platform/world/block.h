#pragma once

#include <stdint.h>

class Block
{
	
public:

	int x, y;
	int8_t nr;
	
	
	Block();
	~Block();
	void free();
};