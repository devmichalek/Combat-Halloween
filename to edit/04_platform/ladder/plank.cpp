#include "plank.h"

Plank::Plank()
{
	x = y = nr = 0;
	red = green = blue = 0;
}

Plank::~Plank()
{
	free();
}

void Plank::free()
{
	x = y = nr = 0;
	red = green = blue = 0;
}