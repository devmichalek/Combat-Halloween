#pragma once

#include <SFML/Graphics/Color.hpp>

class Scope
{
	int x;
	float vel;

	int screen_w;
	sf::Uint8 width;
	
	sf::Uint8 a;
	sf::Uint8 b;
	
public:
	
	Scope();
	~Scope();
	void free();
	
	void set( int x, int width, int screen_w );
	
	void setVel( float vel );
	float getVel();
	
	void setFactor( int factor );
	void move( sf::Uint8 direction );
	int getState();
	
	void setNewX( int distance );
	
	bool getScope();
	bool allowMoving();
};