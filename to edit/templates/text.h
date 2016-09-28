/**
    text.h
    Purpose: class MyText to load and draw text

    @author Adrian Michalek
    @version 2016.09.01
	@email adrmic98@gmail.com
*/


#pragma once
#include "SFML/Graphics.hpp"
#include "templates/border.h"
#include "templates/color.h"

using namespace std;

class MyText :public Border, public Color
{
	string ID;	// Universal
	
	sf::Font* font;
	sf::Text* text;
	
	int size;
	
public:
	
	MyText( int x = 0, int y = 0, sf::Uint8 alpha = 0x00 );
	~MyText();
	void free();
	void setID( string name );		// To find bugs
	
	#ifdef _WIN32
	void setColor( int i );
	#endif
	
	void setFont( string path, int size = 1, sf::Uint8 r = 0x00, sf::Uint8 g = 0x00, sf::Uint8 b = 0x00 );
	void setText( string line );
	
	void setPosition( float x, float y );
	void center( int w, int h, int wm = 0, int hm = 0 );
    void setScale( float w, float h );

    sf::Text& get();
	
	void fadein( int v = 1, int max = 255 );
	void fadeout( int v = 1, int min = 0 );
	
	void setColor( sf::Uint8 r = 0x00, sf::Uint8 g = 0x00, sf::Uint8 b = 0x00 );
	void setSize( int size = 1 );
	
	void setAlpha( sf::Uint8 alpha = 0 );
	
	std::ostream& operator <<( std::ostream& s );	// Print ID, rect and alpha
	void reloadPosition();
};