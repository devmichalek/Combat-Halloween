/**
    explanator.h
    Purpose: class Explanator - shows information

    @author Adrian Michalek
    @version 2017.03.02
	@email adrmic98@gmail.com
*/

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
	
	int counter;
	int line;
	int alpha_line;
	
public:
	
	// Basics.
	Explanator();
	~Explanator();
	void free();
	
	void load( string str );
	void draw( sf::RenderWindow &window );
	
	void fadeout( int i = 1, int min = 0 );
	
	// In additon.
	void run();
	void stop();
	void focus( float x, float y, bool side = true );
};