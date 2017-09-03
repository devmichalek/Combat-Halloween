#pragma once

#include "SFML/Graphics/Color.hpp"
#include <vector>

using namespace std;

class Skeleton
{
	enum Lines
	{
		APPEAR,
		IDLE,
		WALK,
		ATTACK,
		DIE
	};
	
	vector <sf::Uint8> lines;
	float width;
	float scale_x, scale_y;
	
	float armour;
	float damage;
	float velocity;
	float heartpoints;
	float heartpoints_state;
	
	float left, right;
	float centerX;
	float x, y;
	
	float offset;
	int state;
	bool appearwas;
	
	float attack_counter;
	float attack_line;
	
	
public:
	
	Skeleton();
	~Skeleton();
	void free();
	
	// Setters.
	void setLines( vector <sf::Uint8> lines );
	void setWidth( float width );
	void setScale( float scale_x, float scale_y );
	void setArmour( float value );
	void setDamage( float value );
	void setVelocity( float value );
	void setHP( float value );
	void harm( float value );
	void setLeft( float value );
	void setRight( float value );
	void setOffset( float value );
	void setCenterX( float centerX );
	void setPosition( float x, float y );
	
	void moveX( double elapsedTime );
	void turnLeft();
	void turnRight();
	
	void setAppear();
	void setIdle();
	void setWalk();
	void setAttack();
	void setDie();
	
	
	// Getters.
	int getState();
	float getOffset();
	
	float getLeft();
	float getRight();
	float getX();
	float getY();
	float getCenterX();
	
	float getRealX();
	float getRealY();
	float getRealWidth();
	float getRealHeight();
	
	bool isAlive();
	bool ableToAppear();
	bool ableToWalk();
	bool ableToAttack();
	
	float getXScale();
	float getYScale();
	float getHPScale();
	
	float getHP();
	float getArmour();
	
	// The rest.
	void mechanics( double elapsedTime );
};