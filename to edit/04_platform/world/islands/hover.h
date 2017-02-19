#pragma once

#include "04_platform/world/brick/block.h"
#include <vector>

using namespace std;

class Hover	// flying island
{
	vector <Block*> blocks;
	
	int startX, endX;
	int vel;
	int vel_state;
	int state;
	bool awryS;
	
public:
	Hover();
	~Hover();
	void free();
	
	void positioning( int width, int type );
	void setPosition( int startX, int endX, int y, int vel );
	void moveX( float vel );
	void moving( int width );
	void awry();
	
	void turnOff();
	void turnOn();
	
	unsigned getSize();
	int getX( unsigned which );
	int getY( unsigned which );
	int getNr( unsigned which );
};