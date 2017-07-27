#pragma once
#define _GLIBCXX_USE_CXX11_ABI 0
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Image.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include <vector>
#include <iostream>
using namespace std;

class MySprite
{
	string identity;
	sf::Image* image;
    sf::Sprite* sprite;
	sf::Texture* texture;
	vector <sf::IntRect*> rects;
	float alpha;
	
public:

    MySprite();
    ~MySprite();
    void free();
	const sf::Sprite& get() const;	// Return sprite
	
	void setIdentity( string identity );
	const string& getIdentity() const;
	
	void setColor( sf::Color color );
	void setAlpha( float alpha = 0 );
	float getAlpha();
	
	void fadein( float v = 1, int max = 0xFF );
	void fadeout( float v = 1, int min = 0 );
	
	void flipHorizontally();
	void flipVertically();
	
	
	void load( string path, int amount = 1 );
	void create( int w, int h );
	
	
    void setPosition( float x, float y );
	void move( float x, float y );
	void center( float x, float y, int w, int h );
	
	void setRotation( double angle );
	void setScale( float x = 1, float y = 1 );
	void setOffset( int n );
	
	// rest accessors
	const float& getX() const;
	const float& getY() const;
    const float getWidth() const;
    const float getHeight() const;
	
    const float& getLeft() const;
    const float getRight() const;
    const float& getTop() const;
    const float getBot() const;
	
	bool checkCollision( float x, float y, float w = 0, float h = 0 );
	bool checkCollisionCircle( float x, float y );
};