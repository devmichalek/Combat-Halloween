/**
    kunai_bit.h
    Purpose: class Kunai_bit contains position x,y particular shuriken, offset etc. stuff to draw.

    @author Adrian Michalek
    @version 2016.01.15
	@email adrmic98@gmail.com
*/

#pragma once

#include "SFML/Graphics.hpp"

class Kunai_bit
{
	float x, y;
	float vel;
	int which;
	bool active;
	
	sf::Uint8 offset;
	sf::Uint8 line;
	sf::Uint8 delay;
	
public:
	
	Kunai_bit();
	~Kunai_bit();
	void free();
	
	float getX();
	float getY();
	float getVel();
	int getWhich();
	bool isActive();
	sf::Uint8 getOffset();
	
	void setPosition( float sx, float sy, float vel, int which );
	void setAnimation( sf::Uint8 line, sf::Uint8 delay );
	
	void run();
	void destroy();
	void moveX( float vel );
};