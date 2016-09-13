#pragma once

#include "templates/sprite.h"
#include "templates/text.h"

class Music_volume
{
	sf::Uint8 volume;
	MySprite green_bar;
	MySprite white_bar;	// background
	MyText text;		// music || chunk, volume
	
public:
	
	Music_volume( sf::Uint8 vol = 0 );
	~Music_volume();
	
	void load( int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window );
	void handle( sf::Event &event );
};