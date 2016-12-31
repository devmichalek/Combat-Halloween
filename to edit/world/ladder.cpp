#include "world/ladder.h"
#include <cstdlib>

Ladder::Ladder()
{
	x = y = 0;
	nr = 0;
	
	red = rand()%0xFF;
	green = rand()%0xFF;
	blue = 0;
}