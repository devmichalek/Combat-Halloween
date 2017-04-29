/**
    sprite.h
    Purpose: class MySprite to load and draw sprites

    @author Adrian Michalek
    @version 2016.09.22
	@email adrmic98@gmail.com
*/

#pragma once
#include "SFML/Graphics.hpp"
#include "drawable/rect.h"
#include "drawable/color.h"
#include <iostream>

using namespace std;

class MySprite :public Rect, public Color
{
	string name;	// Identity.
	
    sf::Sprite* sprite;
    sf::Texture* texture;
	sf::Image* image;
	
    int nr;		// How many offset's, 0 = blank texture, 1 = loaded image, 1 < sprite.
    int offset;	// Topical offset.
	
	int safe_width;
	int safe_height;
	
	float x_scale;
	float y_scale;
	
public:

    MySprite();
    ~MySprite();
    void free();
	
	void load( string path, int nr = 1 );	// Load.
	void create( int w, int h );	// Create blank texture.
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	
	void setScale( float x = 1, float y = 1 );
	const sf::Sprite& get() const;	// Return sprite
   
    void setPosition( float x, float y );
	void center( int x, int y, int w, int h );
	void setAngle( double angle );
	void setOrigin( int x, int y );
	
	
	
	void setColor( sf::Color color );
	void setAlpha( sf::Uint8 a = 0 );
	
	void setOffset( int n );
	const int& getOffset() const;
	
	void setName( string name );
	const string& getName() const;
	
	
	bool checkPixelCollision( int x, int y );
	
	/*
	bool operator ==( MySprite& mySprite );
	bool operator >( MySprite& mySprite );
	bool operator >=( MySprite& mySprite );
	bool operator <( MySprite& mySprite );
	bool operator <=( MySprite& mySprite );
	std::ostream& operator <<( std::ostream& str );
	*/
};