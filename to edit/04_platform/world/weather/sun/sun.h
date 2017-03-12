#pragma once

#include "drawable/sprite.h"

class Sun
{
	sf::CircleShape* sun;
	float angle;
	int alpha;
	
public:
	
	Sun();
	~Sun();
	void free();
	void reset();
	
	void load( int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window );
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	void setColor( sf::Color color );
	void setStartAngle();
};