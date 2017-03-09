/**
    kunai.h
    Purpose: class Kunai to contain textures, throw kunai, contains 5 kunai.

    @author Adrian Michalek
    @version 2016.12.15
	@email adrmic98@gmail.com
*/

#pragma once

#include <stack>
#include <vector>
#include "drawable/sprite.h"
#include "04_platform/hero/kunai/kunai_bit.h"

class Kunai
{
	float vel;
	float scale;
	
	vector <float> damage;
	vector <Kunai_bit*> bits;
	vector <MySprite*> sprites;
	
public:
	
	Kunai();
	~Kunai();
	void free();
	void load();
	void draw( sf::RenderWindow* &window );
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	unsigned getSize();
	int getX( int which );
	int getW( int which );
	Rect* getRect( int which );
	float getDamage( int which );
	bool isHealKunai( int which );

	void destroy( int which );
	void throwed( int x, int y, bool right, int which );
};