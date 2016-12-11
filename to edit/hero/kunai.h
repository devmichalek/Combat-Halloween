#pragma once

#include "hero/bit.h"
#include <vector>

class Kunai
{
	MySprite sprite;
	vector <Bit*> b;
	float scale;
	
public:
	
	Kunai();
	~Kunai();
	void free();
	
	void load();
	void draw( sf::RenderWindow* &window );
	
	void throwing( int x, int y, int vel );
	
	unsigned int getNr();
	int getX( int which );
	int getY( int which );
	int getW();
	int getH();
	void destroy( int which );
	
	void fadein( int v = 1, int max = 255 );
	void fadeout( int v = 1, int min = 0 );
};