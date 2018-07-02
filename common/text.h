#pragma once
#define _GLIBCXX_USE_CXX11_ABI 0
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include <iostream>
using namespace std;

class MyText
{
	string identity;
	sf::Font* font;
	sf::Text* text;
	float alpha;
	
public:
	
	MyText();
	~MyText();
	void free();
	const sf::Text& get() const;
	sf::Font* &getFont();
	
	void setIdentity( string identity );	// To find errors.
	const string& getIdentity() const;
	
	void setFont( string path );
	// void setFontByFont( sf::Font* &newFont );
	void setText( string line );
	void setTextW( wstring line );
	
	void fadein( float v = 1, int max = 0xFF );
	void fadeout( float v = 1, int min = 0 );
	
	void flipHorizontally();
	void flipVertically();
	
	void setPosition( float x, float y );
	void move( float x, float y );
	void center( float x, float y, int w, int h );
	
	void setScale( float x = 1, float y = 1 );
	void setSize( int size = 1 );
	int getSize();
	void setRotation( float angle );
	
	void setAlpha( float alpha = 0 );
	float getAlpha();
	void setColor( sf::Color color );
	
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
};