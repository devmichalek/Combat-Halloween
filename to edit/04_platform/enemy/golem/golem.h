#pragma once

#include "04_platform/enemy/skeleton/skeleton.h"

class Golem :public Skeleton
{
	enum
	{
		APPEAR = 0,
		WALK,
		ATTACK,
		DEAD
	};
	
public:
	
	Golem();
	~Golem();
	void free();
	void reset( int distance );
	
	// Setters.
	void setX( vector <float> x );
	void setX2( vector <float> x2 );
	void setY( vector <float> y );
	void setLine( vector <sf::Uint8> line );
	void setWidth( vector <int> width );
	void setHeight( vector <int> height );
	void setVelocity( float vel );
	void setDelay( sf::Uint8 delay );
	void setDamage( sf::Uint8 damage );
	void setHeartPoints( int hp );
	void setBorders( int left, int right );
	void setAttackLine( sf::Uint8 attack_line );
	void setScale( float xScale, float yScale );
	void setDead();
	
	
	// Getters.
	float getX();
	float getY();
	
	float getRealX();
	float getRealY();
	float getRealWidth();
	float getRealHeight();
	
	float getAttackX();
	float getAttackY();
	int getAttackWidth();
	int getAttackHeight();
	int getLeft();
	int getRight();
	int getPlane();
	
	int8_t getState();
	sf::Uint8 getOffset();
	sf::Uint8 getDamage();
	float getHorizontalScale();
	float getVerticalScale();
	int getHeartPoints();
	bool isAlive();
	bool harmSomebody();
	
	
	// Activity.
	void appear( Rect* rect );
	void walk( Rect* rect );
	void mechanics();
	void ableAttack();
	void moveX( int vel );
	void harm( int damage );
};