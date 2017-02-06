#pragma once

#include "block.h"
#include <vector>

using namespace std;

class Moving_block
{
	vector <Block*> blocks;
	
	int width;
	int startX, endX;
	int vel;
	int state;
	
public:
	Moving_block();
	~Moving_block();
	void free();
	
	void positioning();
	void setPosition( int startX, int endX, int y, int vel );
	void moveX( float vel );
	void moving();
	
	unsigned getSize();
	int getX( unsigned which );
	int getY( unsigned which );
	int getNr( unsigned which );
};