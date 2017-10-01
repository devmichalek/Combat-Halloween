#pragma once
#include "own/text.h"
#include "own/sprite.h"
#include <SFML/Graphics/RenderWindow.hpp>

class Balloonchat
{
	float screen_w;
	float screen_h;
	
	MyText text;
	MySprite arrow;
	MySprite lefttopborder;
	MySprite square;
	MySprite righttopborder;
	MySprite rightbotborder;
	MySprite bodyvertical;
	MySprite bodyhorizontal;
	
public:
	
	// Basics.
	Balloonchat();
	~Balloonchat();
	void free();
	void load( float screen_w, float screen_h );
	void draw( sf::RenderWindow* &window );
	void fadein( float v = 1, int max = 0xFF );
	void fadeout( float v = 1, int min = 0 );
	
	// Setters.
	void setText( string newtext );
	void setPosition( float x, float y, bool left = false );
};