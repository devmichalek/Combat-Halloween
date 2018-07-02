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
	void draw( sf::RenderWindow* &window, sf::Shader &shader );
	void draw( sf::RenderWindow* &window );
	
	// Setters.
	void setText( string newtext );
	void setPosition( float x, float y, bool left = false );
	
	// Getters.
	float getLeft();
	float getRight();
	float getTop();
	float getBot();
	float getWidth();
	float getHeight();
};