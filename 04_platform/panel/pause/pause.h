#pragma once

#include "drawable/text.h"
#include "drawable/sprite.h"

class Pause
{
	MyText text;
	MySprite sprite;
	
	bool focus;
	bool paused;
	bool allowed;
	
public:
	
	Pause();
	~Pause();
	void free();
	
	void load( int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window );
	void handle( sf::Event &event );
	
	bool isPaused();
	void allow();
};