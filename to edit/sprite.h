/**
    sprite.h
    Purpose: class MySprite to load and draw textures

    @author Adrian Michalek
    @version 2016.09.05
	@email adrmic98@gmail.com
*/

#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

using namespace std;

class MySprite
{
    int w, h;
    int x, y;

    int nr;
    int offset;
	
    sf::Sprite* sprite;
    sf::Texture texture;
	
	int alpha;
	sf::Uint8 r, g, b;

public:

    MySprite( int start_offset = 0, int alpha = 0 );
    ~MySprite();
    void free();
	
    void load( string path, int nr = 0 );
	void create( int w, int h, sf::Uint8 r = 0x00, sf::Uint8 g = 0x00, sf::Uint8 b = 0x00 );	// Create blank texture
	
    void setOffset( int n );
    void setPosition( float x, float y );
	
	int getAlpha();
	void setAlpha( int alpha = 0 );
	
	void setColor( sf::Uint8 r = 0x00, sf::Uint8 g = 0x00, sf::Uint8 b = 0x00 );
    void setScale( float s = 1, float z = 1 );
	
	sf::Sprite& get();
	bool checkCollision( int x, int y, int w = 0, int h = 0 );
	
	void fadein( int i, int max );
	void fadeout( int i, int min );
	
	int getX();
	int getY();
	
    int getWidth();
    int getHeight();
	
    int getLeft();
    int getRight();
	
    int getTop();
    int getBot();
};
