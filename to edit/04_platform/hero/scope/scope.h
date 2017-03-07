/**
    scope.h
    Purpose: class Scope responsible for changing view - It means that sometimes hero moves and sometimes other stuff moves.

    @author Adrian Michalek
    @version 2017.01.28
	@email adrmic98@gmail.com
*/

#pragma once

#include <SFML/Graphics/Color.hpp>

class Scope
{
	float vel;
	
	// states a- hero, b- brick
	sf::Uint8 a;
	sf::Uint8 b;
	
public:
	
	Scope();
	~Scope();
	void free();

	void setVel( float vel );
	float getVel();
	
	void setFactor( int factor );
	void changeMind();
	void move( int x, int screen_w );
	int getState();
	void transform();
		
	bool getScope();
	sf::Uint8 getFactor();
	bool allowMoving();
	
	void reset();
};