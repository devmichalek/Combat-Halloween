#pragma once

#include <SFML/Graphics/Color.hpp>

class Coin
{
	bool active;
	float x, y, yLine;
	float left, right;
	
	int jump;
	sf::Uint8 jumpState;
	
	float vel;
	sf::Uint8 direction;
	
	int offset;
	int delay;
	int line;
	
public:
	
	Coin();
	~Coin();
	void free();
	void reset();
	
	void setPosition( float x, float y );
	void setBorders( float left, float right );
	void setJump( int jump );
	void setAsActive();
	void setVelocity( float vel );
	void setDirection( sf::Uint8 direction );
	void setLine( int line );
	void setDelay( int delay );
	
	int getOffset();
	int getX();
	int getY();
	bool isActive();
	
	bool mechanics();
	void moveX( float vel );
};