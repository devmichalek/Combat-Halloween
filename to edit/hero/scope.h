#pragma once

#include <SFML/Graphics/Color.hpp>

class Scope
{
	int heroX;
	int left, right;
	float vel;
	
	sf::Uint8 state;
	int screen_w;
	sf::Uint8 width;
	
public:
	
	Scope();
	~Scope();
	void free();
	
	void setHeroX( int x );
	void setBorder( int left, int right );
	void setVel( float vel );
	void setWall( int width, int screen_w );
	
	float getVel();
	
	void move( sf::Uint8 direction );
	bool checkWall( int x );
	
	bool allowMoving();
};