#pragma once

#include "templates/sprite.h"
#include "templates/text.h"
#include "menu/parentchunk.h"

class Choice :public Parentchunk
{
	MySprite button;
	MyText text;
	
	int nr;	// number of worlds
	MySprite* world;
	
	MySprite frame;
	
	MyText information;
	
	
	int counter; // random
	int result;	// ended result
	int chosen;	// if user moved on the one of images
	
	// To move - animation
	int range;
	
public:
	
	Choice();
	~Choice();

	void load( int screen_w, int screen_h );
	void handle( sf::Event &event );
	void draw( sf::RenderWindow &window );
	
	void fadein( int j, int max );
	void fadeout( int j, int min );
	
	int getResult();
	int getAlpha();
	bool isChosen();
	
	void reset();
	
	bool move( int vel, int ran );	// move horizontal
};