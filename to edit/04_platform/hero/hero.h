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
		DEAD,
		nr = DEAD +1 // Tells us how many sprites we have.
	};
	
	MySprite* sprite;

	int which;		// Which sprite is active.
	int offset;		// Which offset is active.
	int delay;		// Slow because of FPS.
	
	vector <int*> keys; // Which keys are responsible for particular activity.
	
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
	
	// Harm.
	sf::Uint8 hit_line;
	sf::Uint8 hit_counter;
	
	
	Activity j;		// Jump.
	Activity a;		// Attack.
	Activity ja;	// Jump and attack.
	Activity t;		// Throw.
	Activity jt;	// Jump and throw.
	
	MySprite box;
	MySprite jumpBox;
	
	Rect attackBox;
	Rect jumpAttackBox;
	
	bool scope;
	
	int deathY;
	int deathX;
	bool dead;
	int deadCounter;
	int deadLine;
	
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
	void harm();
	void makeColor();
	
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
	
	void isLastStand( sf::Uint8 block_w, int screen_h );	// set last position where hero stand on the grass block
	bool checkY( int screen_h );	// if y is higher than screen_h then equils -1 heart
	
	const int getX();
	const int getY();
	const int getW();
	const int getH();
	
	
	int strToInt( string s );		// Transform string to int.
	bool checkKeys( int a, int b );	// See if keys are pressed?
	sf::Uint8 getDirection();		// Return 0 = hero is not moving etc.
	bool getSide();					// Return true if hero is directed to the right.
	Rect* getRect();			// Get rectangle of hero.
	
	Hero();
	~Hero();
	void free();
	
	void load( int& screen_w, int& posY, string path );
	void draw( sf::RenderWindow* &window );
	
	void fadein( int v = 1, int max = 255 );
	void fadeout( int v = 1, int min = 0 );
};