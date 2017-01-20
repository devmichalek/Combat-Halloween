#pragma once

#include <SFML/Graphics/Color.hpp>

class Scope
{
	float vel;
	
	sf::Uint8 a;
	sf::Uint8 b;
	
public:
	
	Scope();
	~Scope();
	void free();

	void setVel( float vel );
	float getVel();
	
	void setFactor( int factor );
	void move( int x, int screen_w );
	int getState();
	void transform();
		
	bool getScope();
	bool allowMoving();
};