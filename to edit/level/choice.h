#pragma once

#include "templates/sprite.h"
#include "templates/text.h"
#include "menu/parentchunk.h"

class Choice :public Parentchunk
{
	MySprite sprite;
	MyText text;
	MyText number;
	sf::Uint8 counter;
	
	int result;
	
public:
	
	Choice();
	~Choice();

	void load( int screen_w, int screen_h );
	void handle( sf::Event &event );
	void draw( sf::RenderWindow &window );
	
	void fadein( int i, int max );
	void fadeout( int i, int min );
	
	bool isReady();
	int getResult();
};