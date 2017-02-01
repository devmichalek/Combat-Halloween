/**
    color.h
    Purpose: class Color represents 4 sf::Uint8 values.

    @author Adrian Michalek
    @version 2016.09.09
	@email adrmic98@gmail.com
*/

#pragma once

#include <SFML/Graphics/Color.hpp>

class Color
{
	
protected:
	sf::Color color;
	
public:
	
	sf::Color getColor();
	void setColor( sf::Color color );
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	sf::Uint8 getAlpha();
	void setAlpha( sf::Uint8 a = 0 );
};