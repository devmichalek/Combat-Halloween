#pragma once

#include "SFML/Graphics.hpp"
#include <string>

using namespace sf;
using namespace std;

class MySprite
{
    int w, h;
    int x, y;
    float scale;

    int nr;
    int offset;
    Sprite* sprite;
    Texture texture;
	
	int alpha;
	int r, g, b;

public:

    MySprite( int offset = 0, int alpha = 0 );
    ~MySprite();

    void free();

    bool load( string path, int nr = 0 );

    void setOffset( int n );
    void setPosition( float x, float y );
    void setScale( float s );

    Sprite& get();
	
    int getWidth();
    int getHeight();
    int getLeft();
    int getRight();
    int getTop();
    int getBot();
	int getX();
	int getY();
	
	bool checkCollision( int x, int y, int w = 0, int h = 0 );
	
	void fadein( int i, int max );
	void fadeout( int i, int min );
};
