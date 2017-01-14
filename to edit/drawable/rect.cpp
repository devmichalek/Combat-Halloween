#include "drawable/rect.h"
#include <stdio.h>

void Rect::set( int x, int y, int w, int h )
{
	left = x;
	top = y;
	width = w;
	height = h;
}


const int& Rect::getX() const
{
    return left;
}

const int& Rect::getY() const
{
    return top;
}



const int& Rect::getWidth() const
{
    return width;
}

const int& Rect::getHeight() const
{
    return height;
}



const int& Rect::getLeft() const
{
    return left;
}

const int Rect::getRight() const
{
    return left + width;
}



const int& Rect::getTop() const
{
    return top;
}

const int Rect::getBot() const
{
    return top + height;
}


bool Rect::checkCollision( int x, int y, int w, int h )
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