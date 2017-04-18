#include "green.h"

Green::Green()
{
	x = y = 0;
	nr = 0;
	bg = false;
}

Green::~Green()
{
	free();
}

void Green::free()
{
	x = y = 0;
	nr = 0;
	bg = false;
}
