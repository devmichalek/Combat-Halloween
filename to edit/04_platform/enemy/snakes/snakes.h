#pragma once

#include "04_platform/world/brick/block.h"
#include "drawable/rect.h"
#include <SFML/Graphics/Color.hpp>
#include <vector>

using namespace std;

class Snakes
{
protected:
	enum
	{
		APPEAR = 0,
		IDLE,
		ATTACK,
		DEAD
	};
	
	int8_t state;
	sf::Uint8 offset;
	sf::Uint8 delay;
	sf::Uint8 counter;
	vector <sf::Uint8> line;
	
	// alpha
	sf::Uint8 alpha_state;
	sf::Uint8 alpha;
	
	// heart points
	int hp;
	int hp_state;
	
	// scale
	float xScale, yScale;
	
	// attack stuff
	sf::Uint8 attack;
	sf::Uint8 attack_line;
	sf::Uint8 attack_count;
	
	float left;
	vector <float> y;
	vector <float> x;
	vector <int> width;
	vector <int> height;
	
public:
	
	Snakes();
	~Snakes();
	void free();
	void reset( int distance );
	
	// Setters.
	void setX( vector <float> x );
	void setY( vector <float> y );
	void setLine( vector <sf::Uint8> line );
	void setWidth( vector <int> width );
	void setHeight( vector <int> height );
	void setDelay( sf::Uint8 delay );
	void setHeartPoints( int hp );
	void setAttackLine( sf::Uint8 attack_line );
	void setScale( float xScale, float yScale );
	void setLeft( float x );
	void setDead();
	void setAlphaState( sf::Uint8 s );
	void setAlpha( sf::Uint8 a );
	
	
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
	int getPlane();
	sf::Uint8 getAlpha();
	bool alphaAble();
	
	
	int8_t getState();
	sf::Uint8 getOffset();
	float getHorizontalScale();
	float getVerticalScale();
	int getHeartPoints();
	bool isAlive();
	bool harmSomebody();
	
	
	// Activity.
	void appear( float x );
	void mechanics();
	void ableAttack();
	void moveX( float vel );
	void harm( int damage );
};