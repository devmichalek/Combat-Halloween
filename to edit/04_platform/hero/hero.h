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
	vector <MySprite*> sprite;

	int which;			// Which sprite is active.
	unsigned offset;	// Which offset is active.
	unsigned delay;		// Slow because of FPS.
	
	float vel;			// Velocity.
	float jump_vel;		// Jump velocity;
	float grav;			// Gravity.
	float scale;
	
	// Damage.
	float damage;
	
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

	// IDLE
	void idle();
	
	// MOVE
	bool moving();
	void mirrorLeft();
	void mirrorRight();
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
	
	// VEL STUFF AND SCOPE
	float getVel();
	float getJump_vel();
	void setScope( bool scope );
	
	// DEAD
	bool checkFall( int screen_h );
	void setFallenY( int y );
	bool isFallen();
	void undoFallX( sf::Uint8 add );
	void undoFallY();
	void runFallenCounter();
	
	void makeFall();
	void die();
	bool isDead();
	
	const int getX();
	const int getY();
	const int getW();
	const int getH();
	
	
	int strToInt( string s );		// Transform string to int.
	bool checkKeys( int a, int b );	// Which keys are pressed
	sf::Uint8 getDirection();		// Return 0 = hero is not moving etc.
	bool getSide();					// Return true if hero is directed to the right.
	Rect* getRect();				// Get rectangle of hero.
	
	Hero();
	~Hero();
	void free();
	
	void load( int type, int screen_w, int screen_h );
	void setKeys();
	void draw( sf::RenderWindow* &window );
	
	void fadein( int v = 1, int max = 255 );
	void fadeout( int v = 1, int min = 0 );
	void reset( int posY );
	void setColor( sf::Color color );
};