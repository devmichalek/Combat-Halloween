#pragma once

#include "templates/sprite.h"

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
	void start( int vel, int startX, int startY );
	void go();
	
	void reset();
	
	int getX();
	int getY();
	int getVel();
};