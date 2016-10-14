#pragma once

#include "templates/sprite.h"
#include "templates/text.h"
#include "menu/parentchunk.h"

class Choice :public Parentchunk
{
	MySprite button;
	MyText text;
	MyText information;
	
	int counter;
	int result;
	int chosen;
	
	int nr;	// number of worlds
	MySprite* world;
	
	MySprite frame;
	
	bool exit;
	
public:
	
	Choice();
	~Choice();

	void load( int screen_w, int screen_h );
	void handle( sf::Event &event );
	void draw( sf::RenderWindow &window );
	
	void fadein( int j, int max );
	void fadeout( int j, int min );
	
	int getResult();
	bool nextState();
	int getAlpha();
	
	void reset();
};