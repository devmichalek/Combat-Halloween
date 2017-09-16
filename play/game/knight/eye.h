#pragma once

#include "own/sprite.h"
#include <SFML/Graphics.hpp>

class Eye
{
	float screen_w;
	float screen_h;
	
	float line_y;
	float distance_y;
	
	float x, y;
	float scale_x;
	
	MySprite sprite;
	MySprite onlay;
	
	// Shader stuff.
	MySprite shaderSprite;
	sf::Shader shader;
	sf::Clock clock;
	
public:
	
	Eye();
	~Eye();
	void free();
	void reset();
	
	void load( float screen_w, float screen_h );
	void draw( sf::RenderWindow* &window );
	void drawShader( sf::RenderWindow* &window );
	void mechanics( double elapsedTime, float viewX, float viewY );
	
	void fadein( float v = 1, int max = 0xFF );
	void fadeout( float v = 1, int min = 0 );
	
	// Position.
	void setPosition( float x, float y );
};