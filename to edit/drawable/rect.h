/**
    rect.h
    Purpose: class Rect represents rectangle.

    @author Adrian Michalek
    @version 2016.09.10
	@email adrmic98@gmail.com
*/

#pragma once

class Rect
{
	
protected:
	float width;
	float height;
	float left;
	float top;
	
	
public:

	void set( float x, float y, float w, float h );
	
	// accessors
	const float& getX() const;
	const float& getY() const;
    const float& getWidth() const;
    const float& getHeight() const;
	
    const float& getLeft() const;
    const float getRight() const;
    const float& getTop() const;
    const float getBot() const;
	
	bool checkCollision( float x, float y, float w = 0, float h = 0 );
	bool checkRectCollision( Rect rect );
};