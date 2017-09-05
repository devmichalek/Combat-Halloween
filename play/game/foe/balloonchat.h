#pragma once
#include "own/sprite.h"
#include "own/text.h"
#include <SFML/Graphics/RenderWindow.hpp>

class Balloonchat
{
	float width;
	float max_width;
	
	MyText text;
	MySprite lefttopborder;
	MySprite leftbotborder;
	MySprite righttopborder;
	MySprite rightbotborder;
	MySprite bodyvertical;
	MySprite bodyhorizontal;
	
public:
	
	Balloonchat();
	~Balloonchat();
	void free();
	
	void load( float screen_w, float screen_h );
	void draw( sf::RenderWindow* &window );
	
	void fadein( float v = 1, int max = 0xFF );
	void fadeout( float v = 1, int min = 0 );
	
	void setPosition( float x, float y );
	void setText( wstring newtext );
};