#pragma once

#include "drawable/sprite.h"

class Bit
{
	int x, y;
	bool active;
	int vel;
	
public:
	
	Bit();
	~Bit();
	void free();
	
	bool isActive();
	void start( int startX, int startY, int vel );
	void go();
	
	void destroy();
	
	int getX();
	int getY();
	int getVel();
};