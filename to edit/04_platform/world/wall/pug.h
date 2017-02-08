#pragma once

#include "04_platform/world/brick/block.h"
#include <vector>

using namespace std;

class Pug
{
	int vel;
	bool hit;
	int state;
	int startY;
	int surplus;
	
	vector <Block*> blocks;
	
public:

	Pug();
	~Pug();
	void free();
	
	// Support.
	void addBlock( int n, int x, int y );
	
	void positioning( int width, int type );
	void setPosition( int x, int y, int vel, int surplus = 0 );
	void moveX( float vel );
	void moving( int width );
	
	unsigned getSize();
	int getX( unsigned which );
	int getY( unsigned which );
	int getNr( unsigned which );
	
	bool harm( int width );
};