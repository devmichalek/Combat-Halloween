#pragma once

#include "04_platform/world/brick/block.h"
#include <SFML/Graphics/Color.hpp>
#include <vector>

using namespace std;

class Skeleton
{
	int state;
	int offset;
	int delay;
	int counter;
	
	vector <float> y;
	vector <float> x;
	vector <int> line;
	vector <int> width;
	
	int startX;
	int endX;
	
	int hp;
	int hp_state;
	sf::Uint8 damage;
	float vel;
	sf::Uint8 direction;
	
	sf::Uint8 attack;
	sf::Uint8 attack_line;
	
public:
	
	Skeleton();
	~Skeleton();
	void free();
	void reset( int distance );
	
	// Setters.
	void setPosition( vector <float> x, vector <float> y );
	void setLine( vector <int> line, vector <int> width );
	void setDamage( int damage );
	void setHP( int hp );
	void setGlobalX( int startX, int endX );
	
	
	// Getters.
	float getX();
	float getY();
	sf::Uint8 getDamage();
	int getOffset();
	int getNr();
	int get_x_scale();
	bool harmAvailable();
	
	
	// Main
	void appear( int heroX );
	bool alive();
	void walk( int heroX, int heroY, int w );
	void mechanics( int w );
	void ableAttack();
	
	// In action.
	void moveX( int vel );
};