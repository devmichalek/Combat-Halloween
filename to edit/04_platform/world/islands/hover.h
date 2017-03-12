#pragma once

#include "04_platform/world/brick/block.h"
#include <vector>

using namespace std;

class Hover	// flying island
{
	vector <Block*> blocks;
	
	float startX, endX;
	float vel;
	float vel_state;
	int state;
	
public:
	Hover();
	~Hover();
	void free();
	
	void positioning( int width, int type );
	void setPosition( float startX, float endX, float y, float vel );
	void moveX( float vel );
	void moving( int width );
	
	void turnOff();
	void turnOn();
	
	unsigned getSize();
	int getX( unsigned which );
	int getY( unsigned which );
	int getNr( unsigned which );
};