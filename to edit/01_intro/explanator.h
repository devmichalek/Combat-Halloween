#pragma once

#include "drawable/text.h"
#include "drawable/sprite.h"

class Explanator
{
	MyText text;
	MySprite bg;
	
	int alpha;
	int vel;
	int state;
	int screen_w;
	
public:
	
	Explanator();
    ~Explanator();
	void free();

    void load( string str, int screen_w );
    void draw( sf::RenderWindow &window );
	
	void run();
	void stop();
	void focus( int x, int y );
	void fadeout( int i = 1, int min = 0 );
};