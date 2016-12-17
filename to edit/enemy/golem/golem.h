#pragma once

#include "templates/sprite.h"

class Golem
{
	int nr;
	MySprite* sprite;
	
	int which;		// Which sprite is active.
	int offset;		// Which offset is active.
	int delay;		// Slow because of FPS.
	
	float vel;
	float scale;
	bool right;		// Champion is on the left or on the right.
	
	int* offset_nr;	// Golem has different number of offsets per particular animation.
	sf::Uint8 state;		// e. g. appear animation can be used once
	
	float life;
	MySprite life_bar;
	
	
	float centerX;
	float leftX;
	sf::Uint8 hit_line;
	sf::Uint8 hit_counter;
	
	
public:
	
	void setXY( int x, int y );
	void matchX( int x, int w, int y, int h );	// move
	void undoMove();
	
	bool checkHit( Rect* rect, float damage );
	void makeColor();
	
	Golem();
	~Golem();
	void free();
	
	void load();
	void draw( sf::RenderWindow* &window );
	
	void fadein( int v = 1, int max = 255 );
	void fadeout( int v = 1, int min = 0 );
	
	Rect* getRect();
};