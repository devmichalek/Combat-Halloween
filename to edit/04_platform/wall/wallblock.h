#pragma once

#include "04_platform/world/block.h"
#include <vector>

using namespace std;

class WallBlock
{
	int width;
	vector <Block*> blocks;
	
	int vel;
	int startY;
	int state;
	int surplus;
	bool hit;
	
public:

	WallBlock();
	~WallBlock();
	void free();
	
	void positioning();
	void setPosition( int x, int y, int vel, int surplus = 0 );
	void moveX( float vel );
	void moving();
	
	unsigned getSize();
	int getX( unsigned which );
	int getY( unsigned which );
	int getNr( unsigned which );
	int getMainX();
	int getMainR();
	
	bool harm();
};