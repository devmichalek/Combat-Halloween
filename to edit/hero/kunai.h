#pragma once

#include "hero/bit.h"
#include <vector>

class Kunai
{
	MySprite sprite;
	vector <Bit*> bits;
	
	float scale;
	int vel;
	float damage;
	
public:
	
	void throwed( int x, int y, bool right );
	
	unsigned int getNr();
	int getX( int which );
	int getY( int which );
	int getW();
	int getH();
	int getR( int which );
	int getB( int which );
	
	void destroy( int which );
	
	Rect* getRect( int which );
	float getDamage();
	
	Kunai();
	~Kunai();
	void free();
	
	void load();
	void draw( sf::RenderWindow* &window );
	
	void fadein( int v = 1, int max = 255 );
	void fadeout( int v = 1, int min = 0 );
};