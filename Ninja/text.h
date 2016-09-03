#pragma once

#include "SFML/Graphics.hpp"
#include <string>

using namespace std;

class MyText
{
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
	
	bool setFont( string path, int size = 1, int r = 0x00, int g = 0x00, int b = 0x00 );
	bool setText( string line );
	
	void setPosition( float x, float y );
    void setScale( float s );

    sf::Text& get();
	
	bool checkCollision( int x, int y, int w = 0, int h = 0 );
	
	void fadein( int i, int max );
	void fadeout( int i, int min );
	
	void setColor( sf::Uint8 r = 0x00, sf::Uint8 g = 0x00, sf::Uint8 b = 0x00 );
	void setSize( int size = 1 );
	
	int getAlpha();
	void setAlpha( int alpha = 0 );
	
	
	int getWidth();
    int getHeight();
    int getLeft();
    int getRight();
    int getTop();
    int getBot();
	int getX();
	int getY();
};