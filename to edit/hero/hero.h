#pragma once

#include "hero/activity.h"
#include "wood/block.h"
#include <vector>


class Hero
{
	enum
	{
		IDLE = 0,
		RUN,
		THROW,
		ATTACK,
		SLIDE,
		CLIMB,
		GLIDE,
		JUMP,
		JUMP_ATTACK,
		JUMP_THROW,
		DEAD,
		STRENGTH = 10
	};
	
	
	int nr;	// Tell us how many sprites we have.
	MySprite* sprite;
	
	
	float vel;		// Velocity.
	float vel_value;	// Value of velocity set at start.
	int grav;		// Force of gravity.
	int grav_counter;
	
	bool allow_jump;	// If champion stands at the block then can jump.
	bool glide;	// If champion is falling
	bool slide;	// If champion is sliding
	
	
	int which;		// Which activity is active.
	int offset;		// Which offset is active.
	int delay;		// To mould for FPS.
	
	
	bool right;		// Direction.
	int flag;		// For direction.
	bool moving;
	float SCALE;
	
	
	vector <int*> keys; // Which keys are responsible for particular activity.
	
	
	Activity j;	// Jump.
	Activity a; // Attack.
	Activity c; // Climb.
	
	int* w; // widths of sprites
	
public:

	void fadein( int v = 1, int max = 255 );
	void fadeout( int v = 1, int min = 0 );

	int strToInt( string s );
	bool checkKey( int a );
	bool checkKeys( int a, int b );
	
	Hero();
	~Hero();
	void free();
	
	void load( int& screen_w, int& posY, string path );
	void draw( sf::RenderWindow* &window );
	
	void idle();
	bool move();
	bool jump();
	bool attack();
	
	void reverseJump();
	void reverseMove();
	
	void gravitation();
	void weightlessness();
	void gliding();
	
	
	
	const int getX();
	const int getY();
	const int getW();
	const int getH();
};