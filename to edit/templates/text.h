/**
    text.h
    Purpose: class MyText to load and draw text

    @author Adrian Michalek
    @version 2016.09.09
	@email adrmic98@gmail.com
*/


#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

using namespace std;

class MyText
{
	string ID;	// Universal
	
	int w, h;
    int x, y;
	
	sf::Font* font;
	sf::Text* text;
	
	int size;
	
	int alpha;
	sf::Uint8 r, g, b;
	
public:
	
	MyText( int alpha = 0 );
	~MyText();
	void free();
	void setID( string name );		// To find bugs
	
	#ifdef _WIN32
	void setColor( int i );
	#endif
	
	void setFont( string path, int size = 1, sf::Uint8 r = 0x00, sf::Uint8 g = 0x00, sf::Uint8 b = 0x00 );
	void setText( string line );
	
	void setPosition( float x, float y );
    void setScale( float w, float h );

    sf::Text& get();
	bool checkCollision( int x, int y, int w = 0, int h = 0 );
	
	void fadein( int i = 1, int max = 255 );
	void fadeout( int i = 1, int min = 255 );
	
	void setColor( sf::Uint8 r = 0x00, sf::Uint8 g = 0x00, sf::Uint8 b = 0x00 );
	void setSize( int size = 1 );
	
	int getAlpha();
	void setAlpha( int alpha = 0 );
	
	int getX();
	int getY();
	
	int getWidth();
    int getHeight();
	
    int getLeft();
    int getRight();
	
    int getTop();
    int getBot();
	
	std::ostream& operator <<( std::ostream& s );	// Print ID, rect and alpha
};