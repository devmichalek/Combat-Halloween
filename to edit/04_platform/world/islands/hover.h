#pragma once

#include "04_platform/world/brick/block.h"
#include "SFML/Graphics.hpp"
#include <vector>

using namespace std;

class Hover	// flying island
{
	vector <Block*> blocks;
	
	float vel;
	float vel_state;
	bool state;
	bool stand;
	
	float startX;
	float endX;
	
public:
	Hover();
	~Hover();
	void free();
	
	void positioning( int width, int type );
	void setPosition( float startX, float endX, float y, float vel );
	void moveX( float vel );
	void moveX_stand( float vel );
	void mechanics( int width );
	
	void turnOff();
	void turnOn();
	
	unsigned getSize();
	float getMainX();
	float getMainY();
	float getX( unsigned which );
	float getY( unsigned which );
	float getNr( unsigned which );
	
	// world moving...
	void setStand( bool s );
	bool isStand();
	float getVel();
	sf::Uint8 getDirection();
};