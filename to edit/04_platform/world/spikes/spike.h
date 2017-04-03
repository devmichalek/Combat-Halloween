#pragma once

#include "SFML/Graphics.hpp"

class Spike
{
	float x, y;
	sf::Uint8 state;
	int line;
	int counter;
	float vel;
	
public:
	
	Spike();
	~Spike();
	void free();
	void reset( int distance );
	
	void setPosition( float x, float y );
	void setLine( int line );
	void setVel( float vel );
	
	void moveX( sf::Uint8 direction, float vel );
	void undoFall( sf::Uint8 add );
	
	void mechanics( int screen_h, int width );
	
	float getX();
	float getY();
	bool isAlive();
};