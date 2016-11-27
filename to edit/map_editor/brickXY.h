#pragma once

#include "templates/sprite.h"
#include "templates/text.h"

class BrickXY
{
	int width; // width of typical block
	int screen_h;
	
	int brick_nr;
	MySprite* brick;

	int x, y;
	int imx, imy;
	
	string realXY;
	string imagXY;
	
	MyText real;
	MyText imag;
	
	bool action;
	
	int chosen;
	
public:
	
	BrickXY();
    ~BrickXY();
	void free();

    void load( int screen_w, int screen_h );
    void draw( sf::RenderWindow* &window );
	void drawXY( sf::RenderWindow* &window );
    void handle( sf::Event &event );
	
	void getImag( int imx, int imy );
	int getPlatform();
};