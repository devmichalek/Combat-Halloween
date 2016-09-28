#pragma once

class Border
{
	
protected:
	int width;
	int height;
	int left;
	int top;
	
	
public:

	void set( int x, int y, int w, int h );
	
	int getX();
	int getY();
    int getWidth();
    int getHeight();
	
    int getLeft();
    int getRight();
    int getTop();
    int getBot();
	
	bool checkCollision( int x, int y, int w = 0, int h = 0 );
};