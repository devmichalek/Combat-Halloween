#include "block.h"

Block::Block()
{
	x = y = 0;
	nr = 0;
}

Block::~Block()
{
	free();
}

void Block::free()
{
	x = y = 0;
	nr = 0;
}