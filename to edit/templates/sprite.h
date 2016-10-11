/**
    sprite.h
    Purpose: class MySprite to load and draw sprites

    @author Adrian Michalek
    @version 2016.09.22
	@email adrmic98@gmail.com
*/

#pragma once
#include "SFML/Graphics.hpp"
#include "border.h"
#include "color.h"
#include <iostream>

using namespace std;

class MySprite :public Border, public Color
{
	string name;		// Identity
    sf::Sprite* sprite;
    sf::Texture* texture;
	
	
    int nr;		// How many offset's, 0 = blank texture, 1 = loaded image, 1 < image with offsets
    int offset;	// Topical offset
	
	
public:

    MySprite( int x = 0, int y = 0, sf::Uint8 alpha = 0x00 );
    ~MySprite();
    void free();	// Delete everything
	
	
	sf::Sprite& get();						// Return sprite
    void load( string path, int nr = 1 );	// Load texture
	void create( int w, int h );			// Create blank texture
	
	
    void setPosition( float x, float y );
	void center( int x, int y, int w, int h );
	
	
	std::ostream& operator <<( std::ostream& str );	// Print name, rect, alpha
	bool operator ==( MySprite& mySprite );			// Return true if we have the same size, color, name
	bool operator >( MySprite& mySprite );
	bool operator >=( MySprite& mySprite );
	bool operator <( MySprite& mySprite );
	bool operator <=( MySprite& mySprite );
	
	
	// const string& getTypeId();
	
	
	void fadein( int v = 1, int max = 255 );
	void fadeout( int v = 1, int min = 0 );
	
	void setColor( sf::Color color );
	void setAlpha( sf::Uint8 a = 0 );
	
	int getOffset();
	void setOffset( int n );
	
	void setScale( float x = 1, float y = 1 );
	
	string getName();
	void setName( string name );
};
