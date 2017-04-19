#pragma once

#include "drawable/sprite.h"

class Scroll
{
	MySprite area;
	MySprite button;
	
	MySprite info;
	float info_x;
	
	bool handled;
	sf::Uint8 vel;
	bool moved;
	
public:
	
	Scroll();
    ~Scroll();
	void free();
	void reset();

    void load( int screen_w, int screen_h );
    void draw( sf::RenderWindow* &window );
	void handle( sf::Event &event );
	
	bool isMoved();
	float getDistance();
	
	void fadein( int i = 1, int max = 255 );
	void fadeout( int i = 1, int min = 0 );
};