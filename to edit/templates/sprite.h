/**
    sprite.h
    Purpose: class MySprite to load and draw sprites

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
	string name;	// Identity
	
	sf::Uint8* pixels;
    sf::Sprite* sprite;
    sf::Texture* texture;
	
	sf::Color color;
	sf::IntRect rect;
	
    int nr;					// How many offset's, 0 = blank texture, 1 = loaded image, > 1 image with offsets
    int offset;				// Topical offset
	
	
public:

    MySprite();
    ~MySprite();
    void free();
	void setName( string name );
	
	
    void load( string path, int nr = 1 );
	void create( int w, int h, sf::Color color );	// Create blank texture
	
	
    void setPosition( float x, float y );
	void setColor( sf::Color color );
    void setScale( float x = 1, float y = 1 );
	
	
	bool checkCollision( int x, int y, int w = 0, int h = 0 );
	void fadein( int i, int max );
	void fadeout( int i, int min );
	
	
	sf::Uint8 getAlpha();
	void setAlpha( sf::Uint8 a = 0 );
	
	int getX();
	int getY();
    int getWidth();
    int getHeight();
	
    int getLeft();
    int getRight();
    int getTop();
    int getBot();
	
	void setOffset( int n );
	int getOffset();
	
	sf::Sprite& get();
	std::ostream& operator <<( std::ostream& s );	// Print ID, rect, alpha
};
