/**
    rect.h
    Purpose: class Rect represents rectangle.

    @author Adrian Michalek
    @version 2016.09.10
	@email adrmic98@gmail.com
*/

#include "drawable/rect.h"
#include <stdio.h>

void Rect::set( float x, float y, float w, float h )
{
	left = x;
	top = y;
	width = w;
	height = h;
}


const float& Rect::getX() const
{
    return left;
}

const float& Rect::getY() const
{
    return top;
}



const float& Rect::getWidth() const
{
    return width;
}

const float& Rect::getHeight() const
{
    return height;
}



const float& Rect::getLeft() const
{
    return left;
}

const float Rect::getRight() const
{
    return left + width;
}



const float& Rect::getTop() const
{
    return top;
}

const float Rect::getBot() const
{
    return top + height;
}


bool Rect::checkCollision( float x, float y, float w, float h )
{
	if( y + h <= top )
        return false;

    if( y >= top + height )
        return false;

    if( x + w <= left )
        return false;

    if( x >= left + width )
        return false;

    return true;
}

bool Rect::checkRectCollision( Rect rect )
{
	if( rect.getY() +rect.getHeight() <= top )
        return false;

    if( rect.getY() >= top + height )
        return false;

    if( rect.getX() + rect.getWidth() <= left )
        return false;

    if( rect.getX() >= left + width )
        return false;

    return true;
}