#pragma once

#include "templates/sprite.h"
#include "templates/text.h"

class Music_volume
{
	int volume;
	int last_volume;
	MySprite* green_bar;
	MySprite* white_bar;	// background
	MyText text;		// music || chunk, volume
	
public:
	
	Music_volume( int volume = 1 );
	~Music_volume();
	
	void load( int screen_w, int screen_h, string str );
	void draw( sf::RenderWindow* &window );
	void handle( sf::Event &event );
	
	void fadein( int i, int max );
	void fadeout( int i, int min );
};