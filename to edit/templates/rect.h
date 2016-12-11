#pragma once

class Rect
{
	
protected:
	int width;
	int height;
	int left;
	int top;
	
	
public:

	void set( int x, int y, int w, int h );
	
	// accessors
	const int& getX() const;
	const int& getY() const;
    const int& getWidth() const;
    const int& getHeight() const;
	
    const int& getLeft() const;
    const int getRight() const;
    const int& getTop() const;
    const int getBot() const;
	
	bool checkCollision( int x, int y, int w = 0, int h = 0 );
};