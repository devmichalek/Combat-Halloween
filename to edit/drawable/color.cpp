/**
    color.h
    Purpose: class Color represents 4 sf::Uint8 values.

    @author Adrian Michalek
    @version 2016.09.09
	@email adrmic98@gmail.com
*/

#include "drawable/color.h"

sf::Color Color::getColor()
{
	return color;
}

sf::Uint8 Color::getAlpha()
{
	return color.a;
}