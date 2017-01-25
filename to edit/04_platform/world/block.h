#pragma once

#include <stdint.h>

class Block
{
	
public:
	int8_t nr;
	int x, y;
	
	Block();
	
};

class BG_Block :public Block
{
	
public:
	int8_t x_scale;
	int8_t y_scale;

	BG_Block();
};