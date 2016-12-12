#pragma once

#include "templates/sprite.h"

class Golem
{
	enum
	{
		APPEAR = 15,
		WALK = 6,
		ATTACK = 6,
		DEAD = 7
	};
	
	int state;		// e. g. appear animation can be used once
	
	int nr;
	MySprite* sprite;
	
	int which;		// Which sprite is active.
	int offset;		// Which offset is active.
	int delay;		// Slow because of FPS.
	
	float* leftX;
	float* rightX;
	float centerX;
	
	float scale;
	float vel;
	
	MySprite life_bar;
	float life;
	float hit;
	
	float strength;
	
	int hit_counter;
	bool right;
	
public:
	
	Golem();
	~Golem();
	void free();
	
	void load();
	void setXY( int x, int y );
	void draw( sf::RenderWindow* &window );
	
	void fadein( int v = 1, int max = 255 );
	void fadeout( int v = 1, int min = 0 );
	
	void fitX( int x );
	bool checkCollision( int x, int y, int w, int h );
};