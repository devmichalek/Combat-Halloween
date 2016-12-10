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
		nr = DEAD +1 // Tells us how many sprites we have.
	};
	
	MySprite* sprite;

	int which;		// Which sprite is active.
	int offset;		// Which offset is active.
	int delay;		// Slow because of FPS.
	
	vector <int*> keys; // Which keys are responsible for particular activity.
	
	float vel;		// Velocity.
	float jVel;		// Jump velocity;
	float grav;		// Gravity.
	float scale;
	
	// Move.
	bool flag;
	bool right;
	
	// Glide.
	bool glide;
	
	// Slide.
	bool slide;
	
	
	Activity j;	// Jump.
	Activity a;	// Attack.
	Activity ja; // Jump and attack.
	
public:

	Hero();
	~Hero();
	void free();
	
	void load( int& screen_w, int& posY, string path );
	void draw( sf::RenderWindow* &window );
	
	
	
	void idle();
	bool move();
	bool jump();
	bool attack();
	void gliding();
	void sliding();
	bool jumpAttack();

	void undoMove();
	void undoJump();


	void gravitation();
	void weightlessness();
	
	const int getX();
	const int getY();
	const int getW();
	const int getH();
	
	void fadein( int v = 1, int max = 255 );
	void fadeout( int v = 1, int min = 0 );
	
	int strToInt( string s );
	bool checkKeys( int a, int b );
};