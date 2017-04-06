#pragma once

#include "04_platform/world/brick/block.h"
#include "drawable/rect.h"
#include <SFML/Graphics/Color.hpp>
#include <vector>

using namespace std;

class Skeleton
{
protected:
	enum
	{
		APPEAR = 0,
		IDLE,
		WALK,
		ATTACK,
		DEAD
	};
	
	int8_t state;
	sf::Uint8 offset;
	sf::Uint8 delay;
	sf::Uint8 counter;
	vector <sf::Uint8> line;
	
	// pos x
	float left;
	float right;
	
	// heart points
	int hp;
	int hp_state;
	
	// damage
	sf::Uint8 damage;
	
	// velocity
	float vel;
	
	// direction
	sf::Uint8 direction;
	
	// scale
	float xScale, yScale;
	
	// attack stuff
	sf::Uint8 attack;
	sf::Uint8 attack_line;
	sf::Uint8 attack_count;
	
	vector <float> y;
	vector <float> x;
	vector <float> x2;
	vector <int> width;
	vector <int> height;
	
public:
	
	Skeleton();
	~Skeleton();
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
	void setBorders( float left, float right );
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
	float getLeft();
	float getRight();
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
	void moveX( float vel );
	void harm( int damage );
};