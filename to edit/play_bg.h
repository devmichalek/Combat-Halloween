#pragma once

#include "sprite.h"

class Play_bg
{
	int nr;
	int active;
	MySprite* one;
	MySprite* two;
	
public:
	
	Play_bg();
	~Play_bg();
	void free();
};