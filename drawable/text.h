/**
    text.h
    Purpose: class MyText to load and draw text

    @author Adrian Michalek
    @version 2016.09.01
	@email adrmic98@gmail.com
*/


#pragma once
#include "SFML/Graphics.hpp"
#include "drawable/rect.h"
#include "drawable/color.h"

using namespace std;

class MyText :public Rect, public Color
{
	string name;	// Universal
	
	sf::Font* font;
	sf::Text* text;
	
	int size;
	int safe_width;
	int safe_height;
	
public:
	
	MyText();
	~MyText();
	void free();
	
	void setFont( string path, int size = 1, sf::Uint8 r = 0, sf::Uint8 g = 0, sf::Uint8 b = 0 );
	void setText( string line );
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	
	void setName( string name );	// To find errors.
	const string& getName() const;
	
	void setScale( float x = 1, float y = 1 );
	
	void setPosition( float x, float y );
	void reloadPosition();	// Set the same position as it was.
	void center( int w, int h, int wm = 0, int hm = 0 );
	
	
	const sf::Text& get() const;
	void setAlpha( sf::Uint8 alpha = 0 );
	void setColor( sf::Uint8 r = 0, sf::Uint8 g = 0, sf::Uint8 b = 0 );
	
	void setSize( int size = 1 );
	std::ostream& operator <<( std::ostream& s );
	
	void setRotation( float angle );
};