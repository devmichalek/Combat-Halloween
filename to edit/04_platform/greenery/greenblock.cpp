#include "greenblock.h"

GreenBlock::GreenBlock()
{
	x = y = 0;
	nr = 0;
	bg = false;
}

GreenBlock::~GreenBlock()
{
	free();
}

void GreenBlock::free()
{
	x = y = 0;
	nr = 0;
	bg = false;
}
