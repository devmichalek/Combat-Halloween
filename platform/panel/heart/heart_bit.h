/**
    heart_bit.h
    Purpose: class Heart_bit contains 3 ints: position x, y and alpha channel.

    @author Adrian Michalek
    @version 2017.03.06
	@email adrmic98@gmail.com
*/

#pragma once

#include "platform/world/brick/block.h"

class Heart_bit
{
public:
	
	int x, y;
	int alpha;
	
	Heart_bit();
	~Heart_bit();
	void free();
};