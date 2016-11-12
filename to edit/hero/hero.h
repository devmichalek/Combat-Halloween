#pragma once

#include "templates/sprite.h"
#include <vector>

class Hero
{
	int which;	// which activity is actual
	int offset;	// counter
	int delay;
	const volatile int off_const=0; 	// const how many offsets we have
	
	int nr;
	MySprite* sprite;
	
	vector<int*> keys;
	int vel;
	bool right;
	
	bool jump_is_active;
	int jump_counter;
	int jump_line;
	
	int gravity;
	
	enum Activity
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
		DEAD
	};
	
public:

	int strToInt( string s );
	
	Hero();
	~Hero();
	void free();
	
	void load( int& screen_w, int& y, string path );
	void draw( sf::RenderWindow* &window );
	void handle( sf::Event &event );
	
	void fadein( int v = 1, int max = 255 );
	void fadeout( int v = 1, int min = 0 );
	
	void moveLeft();
	void moveRight();
	void jump();
};