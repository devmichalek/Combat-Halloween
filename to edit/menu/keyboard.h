#pragma once

#include "templates/text.h"
#include "templates/sprite.h"

class Keyboard
{
	int text_nr;
	MyText* text;
	
	MySprite sprite;
	int sprite_offset;
	MySprite shuriken;
	
	MySprite rect;
	
	int focus;
	
	int* keys;
	int keys_nr;
	
	MyText information;
	
public:

	Keyboard();
    ~Keyboard();

    void load( int screen_w, int bot = 10 );
    void draw( sf::RenderWindow &window );
	void handle( sf::Event &event );

	void fadein( int j, int max );
	void fadeout( int j, int min );
	
	int* getHeroKeys();
};