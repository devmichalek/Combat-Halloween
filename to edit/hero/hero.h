#pragma once

#include "templates/sprite.h"
#include <vector>


class Activity
{
	
public:
	int line;
	int counter;
	bool active;
	
	Activity();
	~Activity();
	void free();
	void summarize();
};



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
	
	
	// we need all widths because of scale ( minus etc. )
	int WIDTH_IDLE;
	int WIDTH_RUN;
	int WIDTH_JUMP;
	int WIDTH_ATTACK;
	float SCALE;
	
	
	int nr;	// Tell us how many sprites we have.
	MySprite* sprite;
	
	
	int vel;		// Velocity.
	int vel_value;	// Value of velocity set at start.
	int grav;		// Force of gravity.	
	
	int which;		// Which activity is active.
	int offset;		// Which offset is active.
	int delay;		// To mould for FPS.
	
	
	bool right;		// Direction.
	bool moving;
	
	
	vector <int*> keys; // Which keys are responsible for particular activity.
	
	
	Activity j;	// Jump.
	Activity a; // Attack.
	Activity c; // Climb.
	
public:

	void fadein( int v = 1, int max = 255 );
	void fadeout( int v = 1, int min = 0 );

	int strToInt( string s );
	bool checkKey( int a );
	bool checkKeys( int a, int b );
	
	Hero();
	~Hero();
	void free();
	
	void load( int& screen_w, int& y, string path );
	void draw( sf::RenderWindow* &window );	
	
	void idle();
	bool move();
	bool jump();
	bool attack();
	void reverse();
	
	void gravitation();
	void weightlessness();
	
	const int getX();
	const int getY();
	const int getW();
	const int getH();
};