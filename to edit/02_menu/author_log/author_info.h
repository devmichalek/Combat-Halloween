#pragma once

#include "drawable/sprite.h"
#include "drawable/text.h"

class Author_info
{
	MyText text;
	MyText email;

	float text_x;
	float email_x;
	
public:
	
	Author_info();
    ~Author_info();
	void free();
	void reset();

    void load( int screen_w, int screen_h );
    void draw( sf::RenderWindow* &window );
	
	void fadein( int i = 1, int max = 255 );
	void fadeout( int i = 1, int min = 0 );
	
	void move( float distance );
};