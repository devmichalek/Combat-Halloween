#pragma once
#include "own/sprite.h"
#include <vector>
#include <string>
using namespace std;

class Skeleton
{
	enum Activities
	{
		APPEAR = 0,
		IDLE,
		WALK,
		ATTACK,
		DIE
	};
	
	// Features.
	float armour;
	float damage;
	float velocity;
	float heartpoints, heartpoints_state;
	
	// Position part.
	float x, y;
	float width;
	float centerX;		// The center.
	float left, right;	// Borders.
	float scale_x, scale_y;
	
	// Animation part.
	int state;
	float offset;
	vector <sf::Uint8> lines;
	
	// The rest states.
	bool appearwas;
	int attacks;
	float attack_line;
	float attack_counter;
	
	// When foe is disabled.
	float inactivity_x;
	float inactivity_line;
	float inactivity_counter;
	
	// Texts.
	int chosen_text;
	float text_line;
	float text_counter;
	vector <wstring> texts;
	
public:
	
	// Basics.
	Skeleton();
	~Skeleton();
	void free();
	
	
	// Set and get features.
	void setArmour( float value );
	void setDamage( float value );
	void setVelocity( float value );
	void setHeartpoints( float value );
	void harm( float value );
	float getArmour();
	float getDamage();
	float getVelocity();
	float getHeartpoints();
	float getHPScale();
	
	
	// Position.
	void moveX( double elapsedTime );
	void setPosition( float x, float y );
	void setWidth( float width );
	void setCenterX( float centerX );
	void setBorders( float left, float right );
	void setScale( float scale_x, float scale_y );
	void turnLeft();
	void turnRight();
	float getX();
	float getY();
	float getRealX();
	float getRealY();
	float getRealWidth();
	float getRealHeight();
	float getAttackX();
	float getAttackY();
	float getAttackWidth();
	float getAttackHeight();
	float getCenterX();
	float getLeft();
	float getRight();
	float getXScale();
	float getYScale();
	
	
	// Animation.
	void setState( int value );
	void setOffset( float value );
	void setLines( vector <sf::Uint8> lines );
	int getState();
	float getOffset();
	vector <sf::Uint8> getLines();
	
	
	// The rest states.
	void setAppear();
	void setIdle();
	void setWalk();
	void setAttack();
	void setDie();
	bool isAlive();
	bool ableToAppear();
	bool ableToWalk();
	bool ableToAttack();
	bool isAttacking( bool hide = false );
	void mechanics( double elapsedTime );
	
	
	// Text stuff.
	void addText( wstring line );
	bool showText();
	wstring getText();
};