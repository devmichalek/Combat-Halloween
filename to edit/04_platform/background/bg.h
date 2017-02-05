#pragma once

#include "drawable/sprite.h"
#include <vector>

class Bg
{
	enum
	{
		WATER = 0,
		BLOOD,
		FALL,
		nr
	};
	
	int active;
	int line;
	int counter;
	sf::Uint8 alpha_line;
	
	vector <MySprite*> sprite;
	
public:
	
	Bg();
	~Bg();
	void free();
	void reset();
	
	void load( int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window );
	
	void fadein( int v = 1, int max = 255 );
	void fadeout( int v = 1, int min = 0 );
	
	void runWater();
	void runBlood();
	void runFall();
};