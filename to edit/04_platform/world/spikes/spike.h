#pragma once

#include "SFML/Graphics.hpp"

class Spike
{
protected:
	
	float vel;
	float x, y;
	float startY, endY;
	bool harmed;
	
	sf::Uint8 state;
	sf::Uint8 alpha;
	
public:
	
	Spike();
	~Spike();
	void free();
	void reset( int distance );
	
	void setPosition( float x, float y, float endY );
	void setVel( float vel );
	void setAlpha( sf::Uint8 alpha );
	void doFall();
	
	void moveX( sf::Uint8 direction, float vel );
	void undoFall( sf::Uint8 add );
	void mechanics();
	
	float getX();
	float getY();
	float getEndY();
	sf::Uint8 getAlpha();
	bool isAlive();
	bool ableToHarm();
	void setAsHarmed();
};