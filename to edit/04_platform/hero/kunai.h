/**
    kunai.h
    Purpose: class Kunai and Bit - to contain kunai texture, throw kunai, contains max 6 kunai.

    @author Adrian Michalek
    @version 2016.12.15
	@email adrmic98@gmail.com
*/

#pragma once

#include <vector>
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
	int getW();
	
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