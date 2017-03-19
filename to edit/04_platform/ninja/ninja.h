/**
    hero.h
    Purpose: class Hero contains each hero textures, each mechanics.

    @author Adrian Michalek
    @version 2016.09.15
	@email adrmic98@gmail.com
*/

#pragma once

#include "activity.h"
#include "drawable/sprite.h"
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
		DEAD
	};
	
	vector <int*> keys; // Which keys are responsible for particular activity.
	vector <MySprite*> sprites;
	vector <float> x;
	vector <float> x2;
	vector <float> y;

	int which;			// Which sprite is active.
	unsigned offset;	// Which offset is active.
	unsigned delay;		// Slow because of FPS.
	
	float vel;			// Velocity.
	// float vel_state;	// Velocity state.
	float jump_vel;		// Jump velocity;
	float grav;			// Gravity.
	float scale;		// Scale.
	float damage;		// Damage.
	
	// Move.
	bool right;
	bool move;
	
	// Glide.
	bool glide;
	
	// Slide.
	bool slide;
	
	// Climb.
	sf::Uint8 climb;
	
	// Dead.
	sf::Uint8 dead;
	
	
	Activity j;		// Jump.
	Activity a;		// Attack.
	Activity ja;	// Jump and attack.
	Activity t;		// Throw.
	Activity jt;	// Jump and throw.
	
	// MySprite box;
	// MySprite jumpBox;
	
	bool scope;
	
	// Fall stuff.
	bool fallen;
	int fallenCounter;
	int fallenLine;
	int fallenY;
	
public:
	
	// Basics.
	Hero();
	~Hero();
	void free();
	void reset( int posY );
	// void setFPS( float FPS );
	
	void load( int type, int screen_w, int screen_h, int width );
	void setKeys();
	void draw( sf::RenderWindow* &window );
	
	void fadein( int v = 1, int max = 255 );
	void fadeout( int v = 1, int min = 0 );
	void setColor( sf::Color color );
	
	int getX();
	int getY();
	int getW();
	int getH();
	
	bool checkKeys( int a, int b );	// Which keys are pressed
	sf::Uint8 getDirection();		// Return 0 = hero is not moving etc.
	bool getSide();					// Return true if hero is directed to the right.
	Rect* getRect();				// Get rectangle of hero.
	
	float getVel();
	float getJump_vel();
	void setScope( bool scope );
	
	void die();
	bool isDead();
	bool resume();
	int getOffset();


	// IDLE
	void idle();
	
	// MOVE
	void moveX( float vel );
	void moveY( float vel );
	bool moving();
	void undoMove();
	
	// JUMP
	bool jump();
	void undoJump();
	
	// ATTACK
	bool attack();
	Rect* getAttackBox();
	float getDamage();
	
	// GLIDE
	void gliding();
	bool isGliding();
	
	// SLIDE
	void sliding();
	
	// JUMP WITH ATTACK
	bool jumpAttack();
	
	// JUMP WITH THROW
	bool jumpThrow();
	
	// CLIMB
	void climbing();
	void banClimbing();
	
	// THROW
	bool throwing();
	bool throwed();

	// GRAVITY STUFF
	void gravitation();
	void pixelGravitation();
	void weightlessness();
	
	// DEAD
	bool checkFall( int screen_h );
	void setFallenY( int y );
	bool isFallen();
	void undoFallX( sf::Uint8 add );
	void undoFallY();
	void runFallenCounter();
};