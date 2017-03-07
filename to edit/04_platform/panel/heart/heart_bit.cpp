/**
    heart_bit.h
    Purpose: class Heart_bit contains 3 ints: position x, y and alpha channel.

    @author Adrian Michalek
    @version 2017.03.06
	@email adrmic98@gmail.com
*/

#include "04_platform/panel/heart/heart_bit.h"

Heart_bit::Heart_bit()
{
	x = y = 0;
	alpha = 0;
}

Heart_bit::~Heart_bit()
{
	free();
}

void Heart_bit::free()
{
	x = y = 0;
	alpha = 0;
}